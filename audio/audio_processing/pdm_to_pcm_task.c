/*
 * Copyright 2018 NXP. 
 * This software is owned or controlled by NXP and may only be used strictly in accordance with the
 * license terms that accompany it. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you
 * agree to comply with and are bound by, such license terms. If you do not agree to be bound by the
 * applicable license terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "pdm_to_pcm_task.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

/* Freescale includes. */
#include "board.h"

#include "pdm_pcm_definitions.h"

#include "sln_pdm_mic.h"

#define SLN_DSP
#include "sln_intelligence_toolbox.h"

#include "audio_processing_task.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AMP_DSP_STREAM      0U
#define MIC1_DSP_STREAM     1U
#define MIC2_DSP_STREAM     2U
#define MIC3_DSP_STREAM     3U

#define MIC3_START_IDX      (SAI1_CH_COUNT * PCM_SINGLE_CH_SMPL_COUNT)

#if PDM_MIC_COUNT == 3
#define EVT_PING_MASK 		(MIC1_PING_EVENT | MIC2_PING_EVENT | MIC3_PING_EVENT)
#define EVT_PONG_MASK		(MIC1_PONG_EVENT | MIC2_PONG_EVENT | MIC3_PONG_EVENT)
#elif PDM_MIC_COUNT == 2
#define EVT_PING_MASK 		(MIC1_PING_EVENT | MIC2_PING_EVENT)
#define EVT_PONG_MASK		(MIC1_PONG_EVENT | MIC2_PONG_EVENT)
#else
#error
#endif
/*******************************************************************************
 * Global Vars
 ******************************************************************************/

EventGroupHandle_t g_PdmDmaEventGroup;

#if SAI1_CH_COUNT
__attribute__((aligned(8))) uint32_t g_Sai1PdmPingPong[EDMA_TCD_COUNT][PDM_SAMPLE_COUNT * SAI1_CH_COUNT];

pdm_mic_config_t g_pdmMicSai1 = 
{
    SAI1,
	(USE_SAI1_RX_DATA0_MIC << 0U) | (USE_SAI1_RX_DATA1_MIC << 1U),
	PDM_SAMPLE_RATE_HZ,
	PDM_CAPTURE_SIZE_BYTES,
	PDM_SAMPLE_COUNT,
	kRtOutputFallingEdge
};

__attribute__((aligned(32))) pdm_mic_handle_t g_pdmMicSai1Handle = {0U};
#endif

#if USE_SAI2_MIC
uint32_t g_Sai2PdmPingPong[EDMA_TCD_COUNT][PDM_SAMPLE_COUNT];

pdm_mic_config_t g_pdmMicSai2 =
{
    SAI2,
	kMicChannel1,
	PDM_SAMPLE_RATE_HZ,
	PDM_CAPTURE_SIZE_BYTES,
	PDM_SAMPLE_COUNT,
	kRtOutputFallingEdge
};

__attribute__((aligned(32))) pdm_mic_handle_t g_pdmMicSai2Handle = {0U};
#endif

#if USE_SAI1_RX_DATA0_MIC
uint32_t g_Sai1Mic0[EDMA_TCD_COUNT][PDM_SAMPLE_COUNT];
#endif
#if USE_SAI1_RX_DATA1_MIC
uint32_t g_Sai1Mic1[EDMA_TCD_COUNT][PDM_SAMPLE_COUNT];
#endif

static TaskHandle_t s_audioProcessingTask;
static TaskHandle_t s_thisTaskHandle;
static EventGroupHandle_t s_PdmDmaEventGroup;
static int16_t s_filtOut[PCM_SINGLE_CH_SMPL_COUNT] = {0};
__attribute__((aligned(2))) static pcmPingPong_t s_pcmStream;
static int16_t *s_ampLoopback;
static int16_t s_ampOutput[PCM_SINGLE_CH_SMPL_COUNT * 2];
uint8_t *dspMemPool = NULL;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if USE_SAI2_MIC
void DMA0_DMA16_IRQHandler(void)
{
    PDM_MIC_DmaCallback(&g_pdmMicSai2Handle);
}
#endif
#if SAI1_CH_COUNT
void DMA1_DMA17_IRQHandler(void)
{
    PDM_MIC_DmaCallback(&g_pdmMicSai1Handle);
}
#endif
#if 0
static pdm_mic_status_t pdm_to_pcm_mic_init(uint32_t *numHandles)
{
    pdm_mic_status_t status = kPdmMicSuccess;

    status = PDM_MIC_Init(SAI_USE_COUNT, numHandles);

    // Set valid handles
    for (uint32_t idx = 0; idx < *numHandles; idx++)
    {
        s_saiMicHandleIdx[idx] = idx;
    }

#if (USE_SAI2_MIC)
    if (kPdmMicSuccess == status)
    {
        status = PDM_MIC_SetDmaChannel(s_saiMicHandleIdx[1], BOARD_PDM_DMA, 1, g_Sai2TcdChain);
    }

    if (kPdmMicSuccess == status)
    {
        status = PDM_MIC_SetEventGroup(s_saiMicHandleIdx[1], &s_PdmDmaEventGroup, MIC3_PING_EVENT | MIC3_PONG_EVENT);
    }

    if (kPdmMicSuccess == status)
    {
        s_pdmMicSai2.saiClkFreq = BOARD_PDM_SAI_CLK_FREQ;
        status = PDM_MIC_ConfigMic(s_saiMicHandleIdx[1], &s_pdmMicSai2);
    }
#endif

    if (kPdmMicSuccess == status)
    {
        status = PDM_MIC_SetDmaChannel(s_saiMicHandleIdx[0], BOARD_PDM_DMA, 0, g_Sai1TcdChain);
    }

    if (kPdmMicSuccess == status)
    {
        status = PDM_MIC_SetEventGroup(s_saiMicHandleIdx[0], &s_PdmDmaEventGroup, MIC1_PING_EVENT | MIC1_PONG_EVENT);
    }

    if (kPdmMicSuccess == status)
    {
        s_pdmMicSai1.saiClkFreq = BOARD_PDM_SAI_CLK_FREQ;
        status = PDM_MIC_ConfigMic(s_saiMicHandleIdx[0], &s_pdmMicSai1);
    }

#if (USE_SAI2_MIC)
    if (kPdmMicSuccess == status)
    {
        status = PDM_MIC_StartMic(s_saiMicHandleIdx[1]);
    }
#endif

    if (kPdmMicSuccess == status)
    {
        status = PDM_MIC_StartMic(s_saiMicHandleIdx[0]);
    }


    return status;
}
#endif
static int32_t pdm_to_pcm_dsp_init(uint8_t **memPool)
{
    int32_t dspStatus = kDspSuccess;

    dspStatus = SLN_DSP_Init(memPool, pvPortMalloc);

    if (kDspSuccess == dspStatus)
    {
        dspStatus = SLN_DSP_SetCaptureLength(memPool, PDM_SAMPLE_COUNT * PDM_CAPTURE_SIZE_BYTES);
    }

    if (kDspSuccess == dspStatus)
    {
        dspStatus = SLN_DSP_SetGainFactor(memPool, 3); // changed from 3 RAI
    }

    return dspStatus;
}

int32_t pdm_to_pcm_set_gain(uint8_t u8Gain)
{
    return SLN_DSP_SetGainFactor(&dspMemPool, u8Gain);
}

#if 0
#if SAI1_CH_COUNT == 2
static void pdm_to_pcm_mic_pdm_channel_split(uint32_t pingPongIdx, uint8_t **pdm0, uint8_t **pdm1)
{
    uint32_t idx0 = 0U;
    uint32_t idx1 = 0U;

    for (uint32_t idx = 0; idx < PDM_SAMPLE_COUNT * SAI1_CH_COUNT; idx++)
    {
        if (idx & 0x1)
        {
            s_Sai1Mic1[pingPongIdx][idx1] = s_Sai1PdmPingPong[pingPongIdx][idx];
            idx1++;
        }
        else
        {
            s_Sai1Mic0[pingPongIdx][idx0] = s_Sai1PdmPingPong[pingPongIdx][idx];
            idx0++;
        }
    }
    
    *pdm0 = (uint8_t *)(&s_Sai1Mic0[pingPongIdx][0U]);
    *pdm1 = (uint8_t *)(&s_Sai1Mic1[pingPongIdx][0U]);

}
#endif
#endif
void pdm_to_pcm_stream_formatter(int16_t *pcmBuffer, pdm_pcm_input_event_t micEvent, uint8_t pcmFormat)
{

    uint32_t validEvents = (MIC1_PING_EVENT | MIC2_PING_EVENT | MIC3_PING_EVENT | MIC1_PONG_EVENT | MIC2_PONG_EVENT | MIC3_PONG_EVENT);

    if (validEvents & micEvent)
    {
        uint32_t idxStart    = 0;
        uint32_t idxEnd      = 0;
        uint32_t idxIter     = 0;
        uint32_t pingPongIdx = 0;

        bool isPingEvent = (micEvent & MIC1_PING_EVENT) || (micEvent & MIC2_PING_EVENT) || (micEvent & MIC3_PING_EVENT);
        bool isMicTwoEvent = (micEvent & MIC2_PING_EVENT) || (micEvent & MIC2_PONG_EVENT);
        bool isMicTreEvent = (micEvent & MIC3_PING_EVENT) || (micEvent & MIC3_PONG_EVENT);

        if (isPingEvent)
        {
            pingPongIdx = PCM_PING;
        }
        else
        {
            pingPongIdx = PCM_PONG;
        }

#if PDM_MIC_COUNT == 3
        if (isMicTreEvent)
        {
            idxStart = (pcmFormat) ? 2 : (2 * PCM_SINGLE_CH_SMPL_COUNT);
        }
#else
        isMicTwoEvent = isMicTreEvent;
#endif

        if (isMicTwoEvent)
        {
            idxStart = (pcmFormat) ? 1 : PCM_SINGLE_CH_SMPL_COUNT;
        }

        idxEnd = (pcmFormat) ? PCM_SAMPLE_COUNT : (PCM_SINGLE_CH_SMPL_COUNT + idxStart);

        idxIter = (pcmFormat) ? 2U : 1U;

        for (uint32_t idx = idxStart; idx < idxEnd; idx += idxIter)
        {
            s_pcmStream[pingPongIdx][idx] = *pcmBuffer;
            pcmBuffer++;
        }
    }
}

void pdm_to_pcm_set_task_handle(TaskHandle_t *handle)
{
    if (NULL != handle)
    {
        s_thisTaskHandle = *handle;
    }
}

void pdm_to_pcm_set_audio_proces_task_handle(TaskHandle_t *handle)
{
    if (NULL != handle)
    {
    	s_audioProcessingTask = *handle;
    }
}

TaskHandle_t pdm_to_pcm_get_task_handle(void)
{
    return s_thisTaskHandle;
}

EventGroupHandle_t pdm_to_pcm_get_event_group(void)
{
    return s_PdmDmaEventGroup;
}

void pdm_to_pcm_set_amp_loopback_buffer(uint8_t **buf)
{
    if ((NULL != buf) && (NULL != *buf))
    {
        s_ampLoopback = (int16_t *)(*buf);
    }
}

EventBits_t pdm_to_pcm_get_amp_loopback_event(void)
{
	return (EventBits_t)AMP_REFERENCE_SIGNAL;
}

int16_t *pdm_to_pcm_get_amp_output(void)
{
    return s_ampOutput;
}

int16_t *pdm_to_pcm_get_pcm_output(void)
{
    return (int16_t *)s_pcmStream;
}

uint8_t **pdm_to_pcm_get_mempool(void) {

    return &dspMemPool;
}

void pdm_to_pcm_task(void *pvParameters)
{
    volatile EventBits_t preProcessEvents = 0U;
    volatile EventBits_t postProcessEvents = 0U;
    uint32_t u32AmpIndex = 1;

    pdm_mic_status_t status = kPdmMicSuccess;
    uint32_t numHandles = 0;

    int32_t dspStatus = kDspSuccess;

    s_PdmDmaEventGroup = xEventGroupCreate();

    sln_dsp_states_t eDspState = kDspSuccess;

	g_PdmDmaEventGroup = xEventGroupCreate();

#if SAI1_CH_COUNT
    g_pdmMicSai1Handle.eventGroup = s_PdmDmaEventGroup;
    g_pdmMicSai1Handle.config     = &g_pdmMicSai1;
    g_pdmMicSai1Handle.dma        = DMA0;
    g_pdmMicSai1Handle.dmaChannel = 1U;
    g_pdmMicSai1Handle.dmaIrqNum  = DMA1_DMA17_IRQn;
    g_pdmMicSai1Handle.dmaRequest = (uint8_t)kDmaRequestMuxSai1Rx;
    g_pdmMicSai1Handle.pongFlag   = MIC1_PONG_EVENT;
    g_pdmMicSai1Handle.pingFlag   = MIC1_PING_EVENT;
    g_pdmMicSai1Handle.errorFlag   = PDM_ERROR_FLAG;
    g_pdmMicSai1Handle.pingPongBuffer[0] = (uint32_t *)(&g_Sai1PdmPingPong[0][0]);
    g_pdmMicSai1Handle.pingPongBuffer[1] = (uint32_t *)(&g_Sai1PdmPingPong[1][0]);
#endif

#if USE_SAI2_MIC
    g_pdmMicSai2Handle.eventGroup = s_PdmDmaEventGroup;
    g_pdmMicSai2Handle.config = &g_pdmMicSai2;
    g_pdmMicSai2Handle.dma        = DMA0;
    g_pdmMicSai2Handle.dmaChannel = 0U;
    g_pdmMicSai2Handle.dmaIrqNum  = DMA0_DMA16_IRQn;
    g_pdmMicSai2Handle.dmaRequest = (uint8_t)kDmaRequestMuxSai2Rx;
    g_pdmMicSai2Handle.pongFlag   = MIC3_PONG_EVENT;
    g_pdmMicSai2Handle.pingFlag   = MIC3_PING_EVENT;
    g_pdmMicSai2Handle.errorFlag   = PDM_ERROR_FLAG;
    g_pdmMicSai2Handle.pingPongBuffer[0] = (uint32_t *)(&g_Sai2PdmPingPong[0][0]);
    g_pdmMicSai2Handle.pingPongBuffer[1] = (uint32_t *)(&g_Sai2PdmPingPong[1][0]);
#endif

#if SAI1_CH_COUNT
    PDM_MIC_ConfigMic(&g_pdmMicSai1Handle);
#endif
#if USE_SAI2_MIC
    PDM_MIC_ConfigMic(&g_pdmMicSai2Handle);
#endif

#if USE_SAI1_RX_DATA0_MIC || USE_SAI1_RX_DATA1_MIC
	PDM_MIC_StartMic(&g_pdmMicSai1Handle);
#endif

#if USE_SAI2_MIC
	PDM_MIC_StartMic(&g_pdmMicSai2Handle);
#endif

    if (kPdmMicSuccess != status)
    {
        configPRINTF(("ERROR [%d]: Microphone initialization has failed!\r\n", status));
    }

    SLN_AMP_Read();

    dspStatus = pdm_to_pcm_dsp_init(&dspMemPool);

    uint32_t *dspScratch;
    if (kDspSuccess == dspStatus)
    {
    	dspStatus = SLN_DSP_create_scratch_buf(&dspMemPool, &dspScratch, pvPortMalloc);
    }

    if (kDspSuccess != dspStatus)
    {
        configPRINTF(("ERROR [%d]: DSP Toolbox initialization has failed!\r\n", dspStatus));
    }

    for (;;)
    {

        preProcessEvents = xEventGroupWaitBits(s_PdmDmaEventGroup,  0x00FFFFFF, pdTRUE, pdFALSE, portMAX_DELAY);

        if (preProcessEvents & AMP_REFERENCE_SIGNAL) 
        {
            dspStatus = SLN_DSP_downsample_by_3(&dspMemPool, AMP_DSP_STREAM, s_ampLoopback, PCM_AMP_SAMPLE_COUNT, &s_ampOutput[u32AmpIndex * PCM_SINGLE_CH_SMPL_COUNT]);
            if (u32AmpIndex >= 1) {
            	u32AmpIndex=0;
            } else {
            	u32AmpIndex++;
            }

            postProcessEvents |= AMP_REFERENCE_SIGNAL;
            preProcessEvents &= ~AMP_REFERENCE_SIGNAL;
        }

        if (preProcessEvents & MIC1_PING_EVENT)
        {
#if SAI1_CH_COUNT == 2
            
            if (kDspSuccess != SLN_DSP_pdm_to_pcm_multi_ch(&dspMemPool, 1U, 2U, &(g_Sai1PdmPingPong[0U][0U]), &(s_pcmStream[0][0]), dspScratch))
            {
                configPRINTF(("PDM to PCM Conversion error: %d\r\n", kDspSuccess));
            }
#else
            /* Perform PDM to PCM Conversion */
            SLN_DSP_pdm_to_pcm(&dspMemPool, MIC1_DSP_STREAM, (uint8_t *)(&g_Sai1PdmPingPong[0U][0U]), &(s_pcmStream[0U][0U]));

#endif

            postProcessEvents |= MIC1_PING_EVENT;
            postProcessEvents |= MIC2_PING_EVENT;

            preProcessEvents &= ~MIC1_PING_EVENT;
            preProcessEvents &= ~MIC2_PING_EVENT;
        }

        if (preProcessEvents & MIC1_PONG_EVENT)
        {

#if SAI1_CH_COUNT == 2

            if (kDspSuccess != SLN_DSP_pdm_to_pcm_multi_ch(&dspMemPool, MIC1_DSP_STREAM, SAI1_CH_COUNT, &(g_Sai1PdmPingPong[1U][0U]), &(s_pcmStream[1U][0U]), dspScratch))
            {
                configPRINTF(("PDM to PCM Conversion error: %d\r\n", kDspSuccess));
            }

#else

            /* Perform PDM to PCM Conversion */
            SLN_DSP_pdm_to_pcm(&dspMemPool, MIC1_DSP_STREAM, (uint8_t *)(&g_Sai1PdmPingPong[1U][0U]), &(s_pcmStream[1U][0U]));

#endif

            postProcessEvents |= MIC1_PONG_EVENT;
            postProcessEvents |= MIC2_PONG_EVENT;

            preProcessEvents &= ~MIC1_PONG_EVENT;
            preProcessEvents &= ~MIC2_PONG_EVENT;

        }

#if (USE_SAI2_MIC)
        if (preProcessEvents & MIC3_PING_EVENT)
        {
        	GPIO_PinWrite(GPIO2, 12, 1U);

            /* Perform PDM to PCM Conversion */
            SLN_DSP_pdm_to_pcm(&dspMemPool, MIC3_DSP_STREAM, (uint8_t *)(&g_Sai2PdmPingPong[0U][0U]), &(s_pcmStream[0U][MIC3_START_IDX]));

            postProcessEvents |= MIC3_PING_EVENT;
            preProcessEvents &= ~MIC3_PING_EVENT;

            GPIO_PinWrite(GPIO2, 12, 0U);
        }

        if (preProcessEvents & MIC3_PONG_EVENT)
        {

            /* Perform PDM to PCM Conversion */
            SLN_DSP_pdm_to_pcm(&dspMemPool, MIC3_DSP_STREAM, (uint8_t *)(&g_Sai2PdmPingPong[1U][0U]), &(s_pcmStream[1U][MIC3_START_IDX]));

            postProcessEvents |= MIC3_PONG_EVENT;
            preProcessEvents &= ~MIC3_PONG_EVENT;

        }

        if (preProcessEvents & PDM_ERROR_FLAG)
        {
            configPRINTF(("[PDM-PCM] - Missed Event \r\n"));
            preProcessEvents &= ~PDM_ERROR_FLAG;
        }
#else
        postProcessEvents |= MIC3_PING_EVENT;
        postProcessEvents |= MIC3_PONG_EVENT;
#endif

        if (EVT_PING_MASK == (postProcessEvents & EVT_PING_MASK))
        {

            if (NULL == s_audioProcessingTask)
            {
                configPRINTF(("ERROR: Audio Processing Task Handle NULL!\r\n"));
            }
            else
            {
            	xTaskNotify(s_audioProcessingTask, (1U << PCM_PING), eSetBits);
            }

            postProcessEvents &= ~(EVT_PING_MASK);
        }
        else if (EVT_PONG_MASK == (postProcessEvents & EVT_PONG_MASK))
        {

            if (NULL == s_audioProcessingTask)
            {
                configPRINTF(("ERROR: Audio Processing Task Handle NULL!\r\n"));
            }
            else
            {
                xTaskNotify(s_audioProcessingTask, (1U << PCM_PONG), eSetBits);
            }

            postProcessEvents &= ~(EVT_PONG_MASK);
        }
    }
}
