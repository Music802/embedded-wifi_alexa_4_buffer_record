/*
 * Copyright 2018 NXP. 
 * This software is owned or controlled by NXP and may only be used strictly in accordance with the
 * license terms that accompany it. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you
 * agree to comply with and are bound by, such license terms. If you do not agree to be bound by the
 * applicable license terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "fsl_common.h"

typedef enum _rgb_led_color
{
    LED_COLOR_RED,
    LED_COLOR_ORANGE,
    LED_COLOR_YELLOW,
    LED_COLOR_GREEN,
    LED_COLOR_BLUE,
    LED_COLOR_PURPLE,
    LED_COLOR_CYAN,
    LED_COLOR_WHITE,
    LED_COLOR_OFF,
}
rgbLedColor_t; 

void RGB_LED_SetColor(rgbLedColor_t color);

status_t RGB_LED_Init(void);


