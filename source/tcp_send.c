#include <stdio.h>

#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"

#include "lwip/api.h"
#include "lwip/sys.h"

#include "lwip/tcpip.h"
#include "wwd_network.h"
#include "wwd_constants.h"
#include "netif/ethernet.h"
#include "lwip/dns.h"
#include "audio_processing_task.h"


err_t tcp_start_connection(struct netconn **conn, struct netconn **newconn){
	  err_t err;
	  /* Create a new connection identifier. */
	  /* Bind connection to port number 9007. */
	 // long ms_long;
	//  ms_long = LWIP_SO_SNDRCVTIMEO_GET_MS(optval);
	  *conn = netconn_new(NETCONN_TCP);
	  netconn_bind(*conn, IP_ADDR_ANY, 9007);
	  LWIP_ERROR("tcpecho: invalid conn", (*conn != NULL), return;);

	  /* Tell connection to go into listening mode. */
	  netconn_listen(*conn);
	  netconn_set_recvtimeout(*conn, (u32_t)30000); //30 seconds timeout

	    /* Grab new connection. */
	   err = netconn_accept(*conn, newconn);

	return err;
}



void tcp_send_event(struct netconn *newconn, int eventName, err_t err){
	/* Send a character using TCP connection */
	char data[] = "EVENT: 1";
	if (err == ERR_OK) {
//		if(eventName == glassBreakDetected){
//			strcpy(data,"EVENT: 1");
//		}else{
//			strcpy(data,"EVENT: 2");
//		}
		err = netconn_write(newconn, data, sizeof(data), NETCONN_COPY);
		if (err != ERR_OK) {
			//printf("tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
		}
	}
	return;
}

void tcp_send_audio_buffer(struct netconn *conn, float* data, int data_length, err_t err){
	/* Send a array of 16 bit ints using TCP connection */
	if (err == ERR_OK) {
		err = netconn_write(conn, data, sizeof(float)*data_length, NETCONN_COPY);
		if (err != ERR_OK) {
			//printf("tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
		}
	}
	return;
}
