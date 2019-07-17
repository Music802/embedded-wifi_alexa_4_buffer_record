/*
* The Clear BSD License
* Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
* All rights reserved.
*
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lwip/opt.h"

#if LWIP_NETCONN

#include "wwd_network.h"
#include "wwd_constants.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "netif/ethernet.h"
#include "ethernetif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* IP address configuration. */
#define configIP_ADDR0 192
#define configIP_ADDR1 168
#define configIP_ADDR2 10
#define configIP_ADDR3 71

/* Netmask configuration. */
#define configNET_MASK0 255
#define configNET_MASK1 255
#define configNET_MASK2 255
#define configNET_MASK3 0

/* Gateway address configuration. */
#define configGW_ADDR0 192
#define configGW_ADDR1 168
#define configGW_ADDR2 10
#define configGW_ADDR3 1

static struct netif fsl_netif0;

/*!
 * @brief Initializes lwIP stack.
 */
void add_wlan_interface_static(void)
{
    static struct netif fsl_netif0;
    ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;

    IP4_ADDR(&fsl_netif0_ipaddr, configIP_ADDR0, configIP_ADDR1, 
                                     configIP_ADDR2, configIP_ADDR3);
    IP4_ADDR(&fsl_netif0_netmask, configNET_MASK0, configNET_MASK1, 
                                     configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&fsl_netif0_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, 
                                     configGW_ADDR3);

    netif_add(&fsl_netif0,    &fsl_netif0_ipaddr, &fsl_netif0_netmask, 
              &fsl_netif0_gw, (void*)WWD_STA_INTERFACE,  wlanif_init, 
              tcpip_input);

    netif_set_default(&fsl_netif0);
    netif_set_up(&fsl_netif0);

    PRINTF("\r\n************************************************\r\n");
    PRINTF(" Interface initialized with static addresses\r\n");
    PRINTF("************************************************\r\n");
    PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_ipaddr)[0], ((u8_t *)&fsl_netif0_ipaddr)[1],
           ((u8_t *)&fsl_netif0_ipaddr)[2], ((u8_t *)&fsl_netif0_ipaddr)[3]);
    PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_netmask)[0], ((u8_t *)&fsl_netif0_netmask)[1],
           ((u8_t *)&fsl_netif0_netmask)[2], ((u8_t *)&fsl_netif0_netmask)[3]);
    PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_gw)[0], ((u8_t *)&fsl_netif0_gw)[1],
           ((u8_t *)&fsl_netif0_gw)[2], ((u8_t *)&fsl_netif0_gw)[3]);
    PRINTF("************************************************\r\n");
}

void add_wlan_interface(void)
{
    ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;
    struct dhcp *pdhcp;

    IP4_ADDR(&fsl_netif0_ipaddr, 0, 0, 0, 0);
    IP4_ADDR(&fsl_netif0_netmask, 0, 0, 0, 0);
    IP4_ADDR(&fsl_netif0_gw, 0, 0, 0, 0);

    netif_add(&fsl_netif0,    &fsl_netif0_ipaddr, &fsl_netif0_netmask,
              &fsl_netif0_gw, (void*)WWD_STA_INTERFACE,  wlanif_init,
              tcpip_input);

    netif_set_default(&fsl_netif0);
    netif_set_up(&fsl_netif0);

    PRINTF("Getting IP address from DHCP server\r\n");
    dhcp_start(&fsl_netif0);
    pdhcp = (struct dhcp *)netif_get_client_data(&fsl_netif0,
                                            LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);
    while(pdhcp->state != DHCP_STATE_BOUND)
    {
        vTaskDelay(1000);
    }

  //  PRINTF(" IPv4 Address got from DHCP  : %u.%u.%u.%u\r\n",
  //           ((u8_t *)&fsl_netif0.ip_addr.addr)[0],
  //           ((u8_t *)&fsl_netif0.ip_addr.addr)[1],
  //           ((u8_t *)&fsl_netif0.ip_addr.addr)[2],
  //           ((u8_t *)&fsl_netif0.ip_addr.addr)[3]);
}

void pp_dhcp_stop()
{
    dhcp_stop(&fsl_netif0);
    netif_remove(&fsl_netif0);
}
#endif