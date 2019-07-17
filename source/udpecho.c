/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP T stack.
 * CP/IP
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "udpecho.h"
#include "tcpecho.h"

#include "lwip/opt.h"

#if LWIP_NETCONN

#include "lwip/api.h"
#include "lwip/sys.h"


#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "wwd_network.h"
#include "wwd_constants.h"
#include "netif/ethernet.h"
#include "lwip/dns.h"


/*-----------------------------------------------------------------------------------*/
static void
udpecho_thread(void *arg)
{
  struct netconn *conn;
  struct netbuf *buf_rcv, *buf;
  char buffer[200];
  char test[] = "Received";
  char received[20];
  err_t err;
  LWIP_UNUSED_ARG(arg);
  ip_addr_t ipaddr;

IP4_ADDR(&ipaddr, 192,168,0,1); ///192.168.0.1
  conn = netconn_new(NETCONN_UDP);
  netconn_bind(conn, &ipaddr, 9007); //IP_ADDR_ANY
  LWIP_ERROR("udpecho: invalid conn", (conn != NULL), return;);

  while (1) {

    err = netconn_recv(conn, &buf_rcv);

    printf("address: %d\n port: %d\n",netbuf_fromaddr(buf_rcv),netbuf_fromport(buf_rcv));
    if (err == ERR_OK) {
   //     no need netconn_connect here, since the netbuf contains the address
      if(netbuf_copy(buf_rcv, buffer, sizeof(buffer)) != buf_rcv->p->tot_len) {
        printf("netbuf_copy failed\n");
      } else {

        buffer[buf_rcv->p->tot_len] = '\0';
        printf("%s: %s\r\n",test,buffer);

		err = netconn_send(conn, buf_rcv);
		buf=netbuf_new();
		netbuf_ref(buf_rcv,test, sizeof(test));
		err = netconn_send(conn, buf_rcv);
        if(err != ERR_OK) {
          LWIP_DEBUGF(LWIP_DBG_ON, ("netconn_send failed: %d\n", (int)err));
          printf("netconn_send failed!\r\n");
        } else {
          LWIP_DEBUGF(LWIP_DBG_ON, ("got %s\n", buffer));
        }
      }
      netbuf_delete(buf);
      netbuf_delete(buf_rcv);

    }
  }
}


/*-----------------------------------------------------------------------------------*/
void
udpecho_init(void)
{
  sys_thread_new("udpecho_thread", udpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}

#endif /* LWIP_NETCONN */
