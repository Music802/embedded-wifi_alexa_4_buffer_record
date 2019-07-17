/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SLN_AMPLIFIER_H__
#define __SLN_AMPLIFIER_H__

#include "fsl_common.h"
#include "fsl_edma.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "pdm_pcm_definitions.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef int32_t amplifier_status_t;

#if (USE_WM8960 && USE_RT1050_EVKB) || USE_TFA9894
/* Macro for SAI TX */
#if USE_RT1050_EVKB
#define DEMO_SAI_OUT SAI1
#else
#define DEMO_SAI_OUT SAI3
#endif
/* I2C instance and clock */
#define DEMO_I2C LPI2C1
/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define DEMO_LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define DEMO_LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define DEMO_I2C_CLK_FREQ ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (DEMO_LPI2C_CLOCK_SOURCE_DIVIDER + 1U))
/* Select Audio/Video PLL (786.48 MHz) as sai1 clock source */
#define DEMO_SAI_CLOCK_SOURCE_SELECT (2U)
/* Clock pre divider for sai1 clock source */
#define DEMO_SAI_CLOCK_SOURCE_PRE_DIVIDER (0U)
/* Clock divider for sai1 clock source */
#define DEMO_SAI_CLOCK_SOURCE_DIVIDER (63U)
/* Get frequency of sai1 clock */
#define DEMO_SAI_CLK_FREQ                                                        \
    (CLOCK_GetFreq(kCLOCK_AudioPllClk) / (DEMO_SAI_CLOCK_SOURCE_DIVIDER + 1U) / \
     (DEMO_SAI_CLOCK_SOURCE_PRE_DIVIDER + 1U))

#if USE_RT1050_EVKB
#define EXAMPLE_SAI_TX_SOURCE kDmaRequestMuxSai1Tx
#define DEMO_SAI_TX_IRQ SAI1_IRQn
#define SAI_UserIRQHandler SAI1_IRQHandler
#else
#define DEMO_SAI_IRQ SAI3_IRQn
#define DEMO_SAI_TX_IRQ SAI3_TX_IRQn
#define DEMO_SAI_RX_IRQ SAI3_RX_IRQn
#define SAI_UserIRQHandler SAI3_TX_IRQHandler
#define SAI_RxUserIRQHandler SAI3_RX_IRQHandler
#define EXAMPLE_SAI_TX_SOURCE kDmaRequestMuxSai3Tx
#endif
#endif


/*******************************************************************************
 * Globals
 ******************************************************************************/
typedef void (* amplifier_callback_t)(void);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus*/

/*! @brief Initialize SAI and DMA for amplifier streaming */
amplifier_status_t SLN_AMP_Init(void);

/*! @brief Start the DMA read */
amplifier_status_t SLN_AMP_Read(void);

amplifier_status_t SLN_AMP_Write(uint8_t *data, uint32_t length);
amplifier_status_t SLN_AMP_WriteNoWait(uint32_t *pu32BuffNum, uint8_t *data, uint32_t length);
amplifier_status_t SLN_AMP_WriteBlocking(uint8_t *data, uint32_t length);
amplifier_status_t SLN_AMP_WriteDefault(void);

amplifier_status_t SLN_AMP_WriteLoop(uint8_t *data, uint32_t length);
amplifier_status_t SLN_AMP_AbortWrite(void);

uint8_t *SLN_AMP_GetLoopBackBuffer(void);
void SLN_AMP_SetLoopBackEventGroup(EventGroupHandle_t *eventGroup);
void SLN_AMP_SetLoopBackEventBits(EventBits_t event);

void SLN_AMP_SetVolume(uint8_t volume);

#if defined(__cplusplus)
}
#endif /*_cplusplus*/

#endif //__SLN_AMPLIFIER_H__
