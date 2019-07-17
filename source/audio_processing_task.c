/*
 * Copyright 2018 NXP. 
 * This software is owned or controlled by NXP and may only be used strictly in accordance with the
 * license terms that accompany it. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you
 * agree to comply with and are bound by, such license terms. If you do not agree to be bound by the
 * applicable license terms, then you may not retain, install, activate or otherwise use the software.d
 */

#include "stdio.h"
 
#include "audio_processing_task.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "limits.h"
#include "queue.h"
#include "event_groups.h"
#include "semphr.h"
#include "board.h"

/* Freescale includes. */
#include "pdm_pcm_definitions.h"
#include "fsl_sai.h"
#include "fsl_sai_edma.h"
//#include "fsl_debug_console.h"

#define SLN_Voice
#include "sln_intelligence_toolbox.h"

/* RealityAI includes */
#include "RealityAI_sound_classifier.h"
#include "sln_RT10xx_RGB_LED_driver.h"
#include "err.h"
#include "timers.h"
/* Wifi */
#include "wifi_wwd/WWD/wwd.h"
#include "wifi_wwd/WWD/wwd_wiced.h"
#include "lwip/tcpip.h"
#include "wwd_network.h"
#include "wwd_constants.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "netif/ethernet.h"
#include "lwip/dns.h"

#include "lwip/api.h"
#include "lwip/sys.h"

extern uint32_t SLN_AMAZON_WAKE_Initialize();
extern void SLN_AMAZON_WAKE_SetWakeupDetectedParams(uint8_t *pu8Wake, uint16_t *pu16WWLen);
extern uint32_t SLN_AMAZON_WAKE_ProcessWakeWord(int16_t * pi16AudioBuff, uint16_t u16BufferSize);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RUN_GENERATED_TEST		(0U)
#define BUFFER_SIZE (PCM_SAMPLE_COUNT * 3)
#define BUFFER_NUM (4)

#define AUDIO_QUEUE_NUM_ITEMS		75U
#define AUDIO_QUEUE_WATERMARK       15U
#define AUDIO_QUEUE_ITEM_LEN_BYTES	(PCM_SAMPLE_SIZE_BYTES * PCM_SINGLE_CH_SMPL_COUNT)
#define AUDIO_QUEUE_WTRMRK_BYTES    (AUDIO_QUEUE_WATERMARK * AUDIO_QUEUE_ITEM_LEN_BYTES)
#define AUDIO_QUEUE_LENGTH_BYTES    (AUDIO_QUEUE_NUM_ITEMS * AUDIO_QUEUE_ITEM_LEN_BYTES)
/*******************************************************************************
 * Global Vars
 ******************************************************************************/

static TaskHandle_t s_appTask;

static SemaphoreHandle_t s_pushCtr;

SDK_ALIGN(uint8_t __attribute__((section(".data.$SRAM_DTC"))) g_externallyAllocatedMem[(173 * 1024)], 8);

static TaskHandle_t s_thisTaskHandle = NULL;
static pcmPingPong_t *s_micInputStream;
static int16_t *s_ampInputStream;
static uint32_t s_numItems = 0;
static uint32_t s_waterMark = 0;
static uint32_t s_outputIndex = 0;

uint8_t  *cloud_buffer;
uint32_t cloud_buffer_len = 0;

//Buffer definitions
float my_buff[WINDOW_LENGTH*2];
int my_buff_length = 0;

//tcp connections
static int initialized = 0;
struct netconn *conn, *newconn;
err_t err;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*! @brief Called to reset the index's to ensure old mic data isn't resent. */
static void audio_processing_reset_mic_capture_buffers()
{
	s_numItems = 0;
	s_waterMark = 0;
	s_outputIndex = 0;
}

void audio_processing_set_app_task_handle(TaskHandle_t *handle)
{
    if ((NULL != handle) && (NULL != *handle))
    {
        s_appTask = *handle;
    }
}

void audio_processing_set_task_handle(TaskHandle_t *handle)
{
    s_thisTaskHandle = *handle;
}

TaskHandle_t audio_processing_get_task_handle(void)
{
    return s_thisTaskHandle;
}

void audio_processing_set_mic_input_buffer(int16_t **buf)
{
    if ((NULL != buf) && (NULL != *buf))
    {
        s_micInputStream = (pcmPingPong_t *)(*buf);
    }
}

void audio_processing_set_amp_input_buffer(int16_t **buf)
{
    if ((NULL != buf) && (NULL != *buf))
    {
        s_ampInputStream = (int16_t *)(*buf);
    }
}

void audio_processing_task(void *pvParameters)
{
    uint8_t pingPongIdx = 0;
    uint8_t *cleanAudioBuff = NULL;
    int32_t status = 0;
    uint8_t pingPongAmpIdx = 0;

    uint32_t taskNotification = 0U;
    uint32_t currentEvent = 0U;

    uint8_t wakeWordActive = 0U;
    uint16_t wwLen = 0;
    sln_afe_configuration_params_t afeConfig;

    //an integer to store the largest value of my_buff
    int max_buf_val;
    int prediction_decay = 0;
    //int my_send_buf_length = 0;

    //the class output of the RealityAI_glass_break_classify() function
    NXP_classes class_output;

    //In the tcp link has not already been initialized
    if(!initialized){

    	RGB_LED_SetColor(LED_COLOR_PURPLE);
    	// Initialize the wifi card
    	//APP_NETWORK_Init();
    	wiced_wlan_connectivity_init();
   		// Initialize as an access point
   		test_apsta(0, NULL);
   		err = tcp_start_connection(&conn, &newconn);

   		//check for an error
   		if (err!=ERR_OK){
   			//connection failure / timeout
   			RGB_LED_SetColor(LED_COLOR_ORANGE);
            //vTaskDelay(100);
           // RGB_LED_SetColor(LED_COLOR_OFF);
   		}
   		else{
   			//if successful, turn the led off
   			initialized = 1;
   			RGB_LED_SetColor(LED_COLOR_OFF);
   		}
    }

    s_pushCtr = xSemaphoreCreateCounting(2, 0);

    uint32_t reqSize = SLN_Voice_Req_Mem_Size();

    assert(sizeof(g_externallyAllocatedMem) >= reqSize);

    /* Make sure we memset the buffer to zero */
    audio_processing_reset_mic_capture_buffers();

    afeConfig.u16PostProcessedGain = 0x0600;
    afeConfig.u8NumberOfMics = PDM_MIC_COUNT;
    status = SLN_Voice_Init(g_externallyAllocatedMem, &afeConfig);

    if (status != 1){

    }

    SLN_AMAZON_WAKE_Initialize();
    SLN_AMAZON_WAKE_SetWakeupDetectedParams(&wakeWordActive, &wwLen);
    //RealityAI_glass_break_classify_init();

    while (1)
    {
        // Suspend waiting to be activated when receiving PDM mic data after Decimation
        xTaskNotifyWait( 0U, ULONG_MAX, &taskNotification, portMAX_DELAY );

        // Figure out if it's a PING or PONG buffer received
        if (taskNotification & (1U << PCM_PING))
        {
            pingPongIdx = 1U;
            pingPongAmpIdx = 1U;
            currentEvent = (1U << PCM_PING);
        }

        if (taskNotification & (1U << PCM_PONG))
        {
            pingPongIdx = 0U;
            pingPongAmpIdx = 0U;
            currentEvent = (1U << PCM_PONG);
        }

        // Process microphone streams
        int16_t *pcmIn = (int16_t*)((*s_micInputStream)[pingPongIdx]);

        // comment out these lines to turn off alexa
        SLN_Voice_Process_Audio(g_externallyAllocatedMem, pcmIn, &s_ampInputStream[pingPongAmpIdx * PCM_SINGLE_CH_SMPL_COUNT], &cleanAudioBuff, NULL, NULL);

        // Pass output of AFE to wake word (comment these out to turn off alexa)
        SLN_AMAZON_WAKE_ProcessWakeWord(cleanAudioBuff, 320);
        taskNotification &= ~currentEvent;


        //update the buffer for the sound classification
        max_buf_val = update_audio_buffer(my_buff, pcmIn, PCM_SINGLE_CH_SMPL_COUNT);
        my_buff_length += PCM_SINGLE_CH_SMPL_COUNT;
        //my_send_buf_length += PCM_SINGLE_CH_SMPL_COUNT;

        //if the buffer is big enough, classify the audio
        if(my_buff_length >= PREDICTION_BUFFER_LENGTH + PCM_SINGLE_CH_SMPL_COUNT){

        	//check if the audio is close to clipping range
        	if(max_buf_val > 29500){ //31000 //29500
        		xTaskNotify(s_appTask, clippingDetected, eSetBits);
        		shift_and_pad_smoothing_buffers();
        		//tcp_send_event(newconn, clippingDetected, err);
        	//check if the audio is too quiet
        	}else if(max_buf_val < 5000){//7168 //8192

        		//if the current quiet sample is close enough to a sample within range, classify it
        		if(prediction_decay > 0) {
        			class_output = RealityAI_glass_break_classify(my_buff);

        			//if glassbreak is detected, notify the apptask and send a tcp packet
        			if(class_output == 1){
        			//	print_smoothing_buffers();
						xTaskNotify(s_appTask, glassBreakDetected, eSetBits);
						if(initialized){
							tcp_send_event(newconn, glassBreakDetected, err);
						}
//						if(my_send_buf_length >= PREDICTION_BUFFER_LENGTH){
//							tcp_send_audio_buffer(newconn, my_buff, PREDICTION_BUFFER_LENGTH, err);
//							my_send_buf_length = 0;
//						}
					}
        		}
        		//shift and pad the buffers, ignore
        		else{
        			xTaskNotify(s_appTask, lowAudioDetected, eSetBits);
        			shift_and_pad_smoothing_buffers();
        		}
        		//decrement the prediction_decay counter
        		prediction_decay--;

        	// The audio is in the correct range,
        	// classify the audio in the buffer using RealityAI_glass_break_classify()
        	}else{
        		class_output = RealityAI_glass_break_classify(my_buff);

        		//if a glassbreak is detected, notify the apptask and send a tcp notice
        		if(class_output == 1){
        		//	print_smoothing_buffers();
        			xTaskNotify(s_appTask, glassBreakDetected, eSetBits);
        			if(initialized){
        				tcp_send_event(newconn, glassBreakDetected, err);
        			}
//        			if(my_send_buf_length >= PREDICTION_BUFFER_LENGTH){
//        				tcp_send_audio_buffer(newconn, my_buff, PREDICTION_BUFFER_LENGTH, err);
//        				my_send_buf_length = 0;
//        			}
        		}

        		//reset the prediction_decay counter
        		prediction_decay=3;
        	}

        	//decriment the buffer length
        	my_buff_length -= STEP_SIZE;
        }
        if (wakeWordActive)
        {
        	wakeWordActive = 0U;
        	// Notify App Task Wake Word Detected
        	xTaskNotify( s_appTask, kWakeWordDetected, eSetBits);
        }
    }
}
