/*
 * Copyright 2018 NXP. 
 * This software is owned or controlled by NXP and may only be used strictly in accordance with the
 * license terms that accompany it. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you
 * agree to comply with and are bound by, such license terms. If you do not agree to be bound by the
 * applicable license terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "fsl_pwm.h"
#include "fsl_xbara.h"
#include "sln_RT10xx_RGB_LED_driver.h"
#include "fsl_device_registers.h"


#define BOARD_PWM_BASEADDR PWM2
#define PWM_SRC_CLK_FREQ CLOCK_GetFreq(kCLOCK_IpgClk)

/* Driver work in progress... more functions could be added */
status_t RGB_LED_Init(void)
{

    /* Structure of initialize PWM */
    pwm_config_t pwmConfig;

    uint16_t deadTimeVal;
    pwm_signal_param_t pwmRed;
    pwm_signal_param_t pwmGreen;
    pwm_signal_param_t pwmBlue;
    uint32_t pwmSourceClockInHz;
    uint32_t pwmFrequencyInHz = 1;

    //CLOCK_SetDiv(kCLOCK_AhbDiv, 0x2); /* Set AHB PODF to 2, divide by 3 */
    //CLOCK_SetDiv(kCLOCK_IpgDiv, 0x3); /* Set IPG PODF to 3, divede by 4 */

	/* Set the PWM Fault inputs to a low value */
    XBARA_Init(XBARA1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm2Fault0);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm2Fault1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault2);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault3);

    PWM_GetDefaultConfig(&pwmConfig);

    /* Allows us to see pwm in Debug Mode*/
    pwmConfig.enableDebugMode = true;

    /* Initialize submodule 0 (Red LED) */
    if (PWM_Init(BOARD_PWM_BASEADDR, kPWM_Module_0, &pwmConfig) == kStatus_Fail)
    {
        //PRINTF("PWM initialization failed\n");
        return kStatus_Fail;
    }
   //pwmConfig.clockSource = kPWM_Submodule0Clock;
    //pwmConfig.initializationControl = kPWM_Initialize_MasterSync;

    /* Initialize submodule 1 (Green LED) */
    if (PWM_Init(BOARD_PWM_BASEADDR, kPWM_Module_1, &pwmConfig) == kStatus_Fail)
    {
       // PRINTF("PWM initialization failed\n");
        return kStatus_Fail;
    }

    /* Initialize submodule 3 (Blue Led) */
    if (PWM_Init(BOARD_PWM_BASEADDR, kPWM_Module_3, &pwmConfig) == kStatus_Fail)
    {
       //PRINTF("PWM initialization failed\n");
        return kStatus_Fail;
    }

    pwmSourceClockInHz = PWM_SRC_CLK_FREQ;

    /* Set deadtime count, we set this to about 650ns */
    deadTimeVal = ((uint64_t)pwmSourceClockInHz * 650) / 1000000000;

    pwmRed.pwmChannel = kPWM_PwmA;
    pwmRed.level = kPWM_LowTrue;
    pwmRed.dutyCyclePercent = 0; /* 0 percent dutycycle */
    pwmRed.deadtimeValue = deadTimeVal;

    pwmGreen.pwmChannel = kPWM_PwmA;
    pwmGreen.level = kPWM_LowTrue;
    pwmGreen.dutyCyclePercent = 0; /* 0 percent dutycycle */
    pwmGreen.deadtimeValue = deadTimeVal;

    pwmBlue.pwmChannel = kPWM_PwmA;
    pwmBlue.level = kPWM_LowTrue;
    pwmBlue.dutyCyclePercent = 0; /* 0 percent dutycycle */
    pwmBlue.deadtimeValue = deadTimeVal;


    /*********** PWMA_SM0 - phase A, configuration, setup 2 channel as an example ************/
    PWM_SetupPwm(BOARD_PWM_BASEADDR, kPWM_Module_0,  &pwmRed, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
                 pwmSourceClockInHz);

    /*********** PWMA_SM1 - phase B configuration, setup PWM A channel only ************/
    PWM_SetupPwm(BOARD_PWM_BASEADDR, kPWM_Module_1, &pwmGreen, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
                 pwmSourceClockInHz);

    /*********** PWMA_SM2 - phase C configuration, setup PWM A channel only ************/
    PWM_SetupPwm(BOARD_PWM_BASEADDR, kPWM_Module_3, &pwmBlue, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz,
                 pwmSourceClockInHz);

    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(BOARD_PWM_BASEADDR,  kPWM_Control_Module_0 |kPWM_Control_Module_1| kPWM_Control_Module_3, true);

    /* Start the PWM generation from Submodules 0, 1 and 3 */
    PWM_StartTimer(BOARD_PWM_BASEADDR, kPWM_Control_Module_0 | kPWM_Control_Module_1|kPWM_Control_Module_3);

    return kStatus_Success;

}

/* Use RGB_LED_SetColor(LED_COLOR_OFF) to turn off LED.
   Will add more functions and tune colors more       */
void RGB_LED_SetColor(rgbLedColor_t color)
{

    uint8_t redPWMval;
    uint8_t greenPWMval;
    uint8_t bluePWMval;

    /*Colours can be tuned more....will continue to add more colours and tuning. */
    switch(color)
    {
        case LED_COLOR_RED:
            redPWMval = 100;
            greenPWMval = 0;
            bluePWMval = 0;
            break;
        case LED_COLOR_ORANGE:
            redPWMval = 100;
            greenPWMval = 60;
            bluePWMval = 0;
            break;
        case LED_COLOR_YELLOW:
            redPWMval = 40;
            greenPWMval = 90;
            bluePWMval = 0;
            break;
        case LED_COLOR_GREEN:
            redPWMval = 0;
            greenPWMval = 100;
            bluePWMval = 0;
            break;
        case LED_COLOR_BLUE:
            redPWMval = 0;
            greenPWMval = 0;
            bluePWMval = 100;
            break;
        case LED_COLOR_PURPLE:
            redPWMval = 60;
            greenPWMval = 0;
            bluePWMval = 100;
            break;
        case LED_COLOR_CYAN:
            redPWMval = 0;
            greenPWMval = 100;
            bluePWMval = 100;
            break;
        case LED_COLOR_WHITE:
            redPWMval = 20;
            greenPWMval = 75;
            bluePWMval = 60;
            break;
        case LED_COLOR_OFF:
            redPWMval = 0;
            greenPWMval = 0;
            bluePWMval = 0;
            break;
        default:
            redPWMval = 0;
            greenPWMval = 0;
            bluePWMval = 0;
            break;
    }


    /* Update duty cycles for all 3 PWM signals */
    PWM_UpdatePwmDutycycle(BOARD_PWM_BASEADDR, kPWM_Module_0, kPWM_PwmA, kPWM_SignedCenterAligned, redPWMval);
    PWM_UpdatePwmDutycycle(BOARD_PWM_BASEADDR, kPWM_Module_1, kPWM_PwmA, kPWM_SignedCenterAligned, (greenPWMval >> 1));
    PWM_UpdatePwmDutycycle(BOARD_PWM_BASEADDR, kPWM_Module_3, kPWM_PwmA, kPWM_SignedCenterAligned, (bluePWMval >> 3));

    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(BOARD_PWM_BASEADDR, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_3, true);

}
