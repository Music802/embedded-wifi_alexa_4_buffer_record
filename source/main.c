/*
 * Copyright 2018 NXP. 
 * This software is owned or controlled by NXP and may only be used strictly in accordance with the
 * license terms that accompany it. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you
 * agree to comply with and are bound by, such license terms. If you do not agree to be bound by the
 * applicable license terms, then you may not retain, install, activate or otherwise use the software.d
 */
#include <stdio.h>
#include <time.h>

/* Board includes */
#include "board.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

/* FreeRTOS kernel includes */
#include "FreeRTOS.h"
#include "task.h"

/* Driver includes */
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "fsl_gpio.h"

#include "sln_RT10xx_RGB_LED_driver.h"
#include "audio_samples.h"

/* Shell includes */
#include "sln_shell.h"

/* Audio processing includes */
#include "pdm_to_pcm_task.h"
#include "audio_processing_task.h"
#include "sln_amplifier.h"

/* Wifi Includes */
#include "lwip/dns.h"
#include "lwip/api.h"
#include "lwip/sys.h"

/* Other includes */
#include "fsl_sdio.h"
#include "fsl_debug_console.h"
#include "semphr.h"
#include "clock_config.h"

/* RealityAI includes */
#include "RealityAI_sound_classifier.h"

/**************************************************/

TaskHandle_t appTaskHandle = NULL;
TaskHandle_t xAudioProcessingTaskHandle = NULL;
TaskHandle_t xPdmToPcmTaskHandle = NULL;
TaskHandle_t appInitDummyNullHandle = NULL;

#define pdm_to_pcm_task_PRIORITY (configMAX_PRIORITIES - 2)
#define audio_processing_task_PRIORITY (configMAX_PRIORITIES - 1)

bool taskPlaying;
uint8_t isRecording;

//tcp connections
/*static int initialized = 0;

struct netconn *conn, *newconn;
err_t err;*/

void appTask(void *arg)
{/*
	if(!initialized){
		// Initialize the wifi card
		APP_NETWORK_Init();
		// Initialize as an access point
		test_apsta(0, NULL);
		err = tcp_start_connection(&conn, &newconn);
		if (err!=ERR_OK){
			printf("TCP connection failure\r\n");
		}
		else{
			initialized = 1;
		}
	}*/

	sln_shell_set_app_init_task_handle(&appInitDummyNullHandle);

	SLN_AMP_Init();

	audio_processing_set_app_task_handle(&appTaskHandle);

    int16_t *micBuf = pdm_to_pcm_get_pcm_output();
    audio_processing_set_mic_input_buffer(&micBuf);

    int16_t *ampBuf = pdm_to_pcm_get_amp_output();
    audio_processing_set_amp_input_buffer(&ampBuf);

    // Create audio processing task
    if (xTaskCreate(audio_processing_task, "Audio_processing_task", 1536U, NULL, audio_processing_task_PRIORITY, &xAudioProcessingTaskHandle) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }

    audio_processing_set_task_handle(&xAudioProcessingTaskHandle);
    pdm_to_pcm_set_audio_proces_task_handle(&xAudioProcessingTaskHandle);

    // Get loopback buffer address from AMP
	uint8_t *ampLoopBackBuf = SLN_AMP_GetLoopBackBuffer();
	pdm_to_pcm_set_amp_loopback_buffer(&ampLoopBackBuf);

	// Set loopback event bit for AMP
	EventBits_t loopBackEvent = pdm_to_pcm_get_amp_loopback_event();
	SLN_AMP_SetLoopBackEventBits(loopBackEvent);

    // Create pdm to pcm task
    if (xTaskCreate(pdm_to_pcm_task, "pdm_to_pcm_task", 1024U, NULL, pdm_to_pcm_task_PRIORITY, &xPdmToPcmTaskHandle) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }

    pdm_to_pcm_set_task_handle(&xPdmToPcmTaskHandle);

    // Pass loopback event group to AMP
    EventGroupHandle_t ampLoopBackEventGroup = NULL;
    while(NULL == ampLoopBackEventGroup)
    {
        ampLoopBackEventGroup = pdm_to_pcm_get_event_group();
        vTaskDelay(10);
    }
    SLN_AMP_SetLoopBackEventGroup(&ampLoopBackEventGroup);

    //RGB_LED_SetColor(LED_COLOR_OFF);

    SLN_AMP_WriteDefault();

    uint32_t taskNotification = 0;
    while(1)
    {

        xTaskNotifyWait( 0xffffffffU, 0xffffffffU, &taskNotification, portMAX_DELAY );

        switch (taskNotification)
        {
        	case kWakeWordDetected:
        	{
            	RGB_LED_SetColor(LED_COLOR_BLUE);
                vTaskDelay(100);
                RGB_LED_SetColor(LED_COLOR_OFF);

                break;
        	}
            case glassBreakDetected:
            {
            	RGB_LED_SetColor(LED_COLOR_RED);
                //tcp_send_data(conn,newconn,err);
                vTaskDelay(100);
                RGB_LED_SetColor(LED_COLOR_OFF);
           	    break;
           	}
            case clippingDetected:
            {
            	RGB_LED_SetColor(LED_COLOR_WHITE);
                vTaskDelay(100);
                RGB_LED_SetColor(LED_COLOR_OFF);
           	    break;
           	}
            case lowAudioDetected:
            {
            	//RGB_LED_SetColor(LED_COLOR_YELLOW);
                //vTaskDelay(100);
                //RGB_LED_SetColor(LED_COLOR_OFF);
            }
           	default:
           		break;
        }

                taskNotification = 0;
    }
}

void main(void)
{
	/* Enable additional fault handlers */
	SCB->SHCSR |= (SCB_SHCSR_BUSFAULTENA_Msk | /*SCB_SHCSR_USGFAULTENA_Msk |*/ SCB_SHCSR_MEMFAULTENA_Msk);

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_BootClockRUN();

    /* Init TCP/IP thread*/
    tcpip_init( NULL, NULL ); // creates the tcp/ip thread

    /*
     * AUDIO PLL setting: Frequency = Fref * (DIV_SELECT + NUM / DENOM)
     *                              = 24 * (32 + 77/100)
     *                              = 786.48 MHz
     */
    const clock_audio_pll_config_t audioPllConfig = {
        .loopDivider = 32,  /* PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
        .postDivider = 1,   /* Divider after the PLL, should only be 1, 2, 4, 8, 16. */
        .numerator = 77,    /* 30 bit numerator of fractional loop divider. */
        .denominator = 100, /* 30 bit denominator of fractional loop divider */
    };

    CLOCK_InitAudioPll(&audioPllConfig);

    CLOCK_SetMux(kCLOCK_Sai1Mux, BOARD_PDM_SAI_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Sai1PreDiv, BOARD_PDM_SAI_CLOCK_SOURCE_PRE_DIVIDER);
    CLOCK_SetDiv(kCLOCK_Sai1Div, BOARD_PDM_SAI_CLOCK_SOURCE_DIVIDER);
    CLOCK_EnableClock(kCLOCK_Sai1);

    CLOCK_SetMux(kCLOCK_Sai2Mux, BOARD_PDM_SAI_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Sai2PreDiv, BOARD_PDM_SAI_CLOCK_SOURCE_PRE_DIVIDER);
    CLOCK_SetDiv(kCLOCK_Sai2Div, BOARD_PDM_SAI_CLOCK_SOURCE_DIVIDER);
    CLOCK_EnableClock(kCLOCK_Sai2);

    edma_config_t dmaConfig = {0};

	/* Create EDMA handle */
	/*
	 * dmaConfig.enableRoundRobinArbitration = false;
	 * dmaConfig.enableHaltOnError = true;
	 * dmaConfig.enableContinuousLinkMode = false;
	 * dmaConfig.enableDebugMode = false;
	 */
	EDMA_GetDefaultConfig(&dmaConfig);
	EDMA_Init(DMA0, &dmaConfig);

	DMAMUX_Init(DMAMUX);

	RGB_LED_Init();
	RGB_LED_SetColor(LED_COLOR_GREEN);

	sln_shell_init();

    xTaskCreate(appTask, "APP_Task", 512, NULL, configMAX_PRIORITIES - 1, &appTaskHandle);
    xTaskCreate(sln_shell_task, "Shell_Task", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);

    /* Run RTOS */
    vTaskStartScheduler();

    /* Should not reach this statement */
    while (1)
    {
    }
}
