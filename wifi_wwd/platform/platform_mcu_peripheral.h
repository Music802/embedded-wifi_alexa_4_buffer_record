/*
 * Copyright 2018, Cypress Semiconductor Corporation or a subsidiary of 
 * Cypress Semiconductor Corporation. All Rights Reserved.
 * 
 * This software, associated documentation and materials ("Software"),
 * is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 * Defines STM32F2xx common peripheral structures, macros, constants and declares STM32F2xx peripheral API
 */
#pragma once
#include "wwd_constants.h"
#include "fsl_device_registers.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/* GPIOA to I */
#define NUMBER_OF_GPIO_PORTS      (8)

/* Interrupt line 0 to 15. Each line is shared among the same numbered pins across all GPIO ports */
#define NUMBER_OF_GPIO_IRQ_LINES  (16)

/* USART1 to 8 where applicable */
#if defined(STM32F446xx) || defined(STM32F40_41xxx)
    #define NUMBER_OF_UART_PORTS      (6)
#endif
#if defined(STM32F427_437xx) || defined(STM32F429_439xx)
    #define NUMBER_OF_UART_PORTS      (8)
#endif
#if defined(STM32F401xx) || defined(STM32F411xE)
    #define NUMBER_OF_UART_PORTS      (3)    // USART1, USART2, and USART6
#endif
#if defined(STM32F412xG)
    #define NUMBER_OF_UART_PORTS      (4)    // USART1, USART2, USART3 and USART6
#endif

/* Invalid UART port number */
#define INVALID_UART_PORT_NUMBER  (0xff)

/* Invalid GPIO port number */
#define INVALID_GPIO_PORT_NUMBER  (0xff)

/* Default STDIO buffer size */
#ifndef STDIO_BUFFER_SIZE
#define STDIO_BUFFER_SIZE         (64)
#endif

/* SPI1 to SPI6 where applicable */
#if defined(STM32F40_41xxx)
#define NUMBER_OF_SPI_PORTS       (3)
#endif
#if defined(STM32F427_437xx) || defined(STM32F429_439xx)
#define NUMBER_OF_SPI_PORTS       (6)
#endif
#if defined(STM32F401xx) || defined(STM32F446xx)
#define NUMBER_OF_SPI_PORTS       (4)
#endif
#if defined(STM32F411xE) || defined(STM32F412xG)
#define NUMBER_OF_SPI_PORTS       (5)
#endif

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/
#define GPIO_TypeDef GPIO_Type

/* GPIO port */
typedef GPIO_TypeDef  platform_gpio_port_t;

typedef struct
{
    platform_gpio_port_t* port;       /* GPIO port. platform_gpio_port_t is defined in <WICED-SDK>/MCU/<MCU>/platform_mcu_interface.h */
    uint8_t               pin_number; /* pin number. Valid range is defined in <WICED-SDK>/MCU/<MCU>/platform_mcu_interface.h         */
} platform_gpio_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

