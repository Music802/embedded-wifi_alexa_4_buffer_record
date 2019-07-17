#include "wifi_wwd/WWD/wwd.h"
#include "wifi_wwd/WWD/wwd_wiced.h"
#include "lwip/tcpip.h"
#include "wwd_network.h"
#include "wwd_constants.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "netif/ethernet.h"
#include "lwip/dns.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* IP address configuration. */
#define configIP_ADDR0 192
#define configIP_ADDR1 168
#define configIP_ADDR2 10
#define configIP_ADDR3 39

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

typedef struct
{
    uint8_t length;                  /**< psk length */
    uint8_t value[WSEC_MAX_PSK_LEN]; /**< actual psk value */
} wiced_psk_t;

typedef struct wifi_cred
{
    wiced_ssid_t ssid;
    wiced_psk_t  password;
} wifi_cred_t;

wwd_result_t wwd_wifi_leave( wwd_interface_t interface );
wiced_result_t register_link_events(wiced_security_t security, void *);
wwd_result_t wifi_if_add(bool use_dhcp);
void pp_dhcp_stop();
extern wiced_result_t wiced_wlan_connectivity_init( void );
static wifi_cred_t s_wifi_cred = {0};
static wiced_security_t auth_type = WICED_SECURITY_WPA2_MIXED_PSK;
/*******************************************************************************
 * Code
 ******************************************************************************/

static wwd_result_t wlan_connectivity_init(void)
{
    wwd_result_t err = WWD_SUCCESS;
    (void) host_rtos_delay_milliseconds( (uint32_t) 1000 );

    /* Main function to initialize wifi platform */
//    configPRINTF(("Initializing WiFi Connectivity ...\r\n"));
//    printf("Initializing Wifi Connectivity...\r\n");
    if((err = wiced_wlan_connectivity_init()) != WWD_SUCCESS)
    {
//        configPRINTF(("Could not initialize WiFi Connectivity, error: %d \r\n", err));
//        printf("Could not initialize WiFi Connectivity, error: %d \r\n", err);
        assert(err == WWD_SUCCESS);
    }

    return err;
}

static wwd_result_t wifi_join(void)
{
    wwd_result_t err = WWD_SUCCESS;

    (void) host_rtos_delay_milliseconds( (uint32_t) 1000 );

    auth_type = s_wifi_cred.password.length ? WICED_SECURITY_WPA2_MIXED_PSK : WICED_SECURITY_OPEN;

    configPRINTF(("Joining %s\r\n", s_wifi_cred.ssid.value));
 //   printf("Joining %s\r\n", s_wifi_cred.ssid.value);
    err = wwd_wifi_join(&s_wifi_cred.ssid,
                        auth_type,
                        s_wifi_cred.password.value,
                        s_wifi_cred.password.length,
                        NULL,
                        WWD_STA_INTERFACE);
    if(err != WWD_SUCCESS)
    {
 //       printf("Failed to join %s, error: %d\r\n", s_wifi_cred.ssid.value, err);
    }
    else
    {
 //       printf("Successfully joined %s\r\n", s_wifi_cred.ssid.value);
    }

    (void) host_rtos_delay_milliseconds( (uint32_t) 1000 );

    return err;
}


// Init the Network
// Set the Wifi SSID and Password
// Join the Wifi
void APP_NETWORK_Init(bool use_dhcp)
{
	ip4_addr_t ipaddr;
    wwd_result_t err = WWD_SUCCESS;

    wlan_connectivity_init();

    //Connect to a Wifi Network
//
//    strcpy((char *)s_wifi_cred.ssid.value, "SR2Group-2.4");
//    s_wifi_cred.ssid.length = 12;
//    strcpy((char *)s_wifi_cred.password.value, "llabwonS!Snowball");
//    s_wifi_cred.password.length = 17;
//    while (1)
//    {
//        err = wifi_join();
//
//        if (err != WWD_SUCCESS)
//        {
//            configPRINTF(("Joining network failed"));
//            printf("Joining network failed\r\n");
//            (void) host_rtos_delay_milliseconds( (uint32_t) 1000 );
//            vTaskSuspend(NULL);
//        }
//        else
//        {
//            break;
//        }
//    }
//   wifi_if_add(0);
    return;
}

wwd_result_t wifi_if_add(bool use_dhcp)
{
    static struct netif ip_netif;
    ip4_addr_t ipaddr, netmask, gw;
    struct dhcp *dhcp;
    wwd_result_t err = WWD_SUCCESS;

    (void) host_rtos_delay_milliseconds( (uint32_t) 1000 );

    if (use_dhcp)
    {
        IP4_ADDR(&ipaddr, 0, 0, 0, 0);
        IP4_ADDR(&netmask, 0, 0, 0, 0);
        IP4_ADDR(&gw, 0, 0, 0, 0);
    }
    else
    {
        IP4_ADDR(&ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
        IP4_ADDR(&netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
        IP4_ADDR(&gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);
    }

    netif_add(&ip_netif, &ipaddr, &netmask, &gw, (void*)WWD_STA_INTERFACE,  wlanif_init, tcpip_input);
    netif_set_default(&ip_netif);
    netif_set_up(&ip_netif);

    if (use_dhcp)
    {
        configPRINTF(("Getting IP address from DHCP ...\r\n"));
  //      printf("Getting IP address from DHCP ...\r\n");
        dhcp_start(&ip_netif);

        dhcp = (struct dhcp *)netif_get_client_data(&ip_netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);
        while (dhcp->state != DHCP_STATE_BOUND)
            vTaskDelay(1000);

        if (dhcp->state == DHCP_STATE_BOUND)
        {
            configPRINTF(("IPv4 Address: %u.%u.%u.%u\r\n", ((u8_t *)&ip_netif.ip_addr.addr)[0],
                          ((u8_t *)&ip_netif.ip_addr.addr)[1], ((u8_t *)&ip_netif.ip_addr.addr)[2],
                          ((u8_t *)&ip_netif.ip_addr.addr)[3]));
   //         printf("IPv4 Address: %u.%u.%u.%u\r\n", ((u8_t *)&ip_netif.ip_addr.addr)[0],
   //                                   ((u8_t *)&ip_netif.ip_addr.addr)[1], ((u8_t *)&ip_netif.ip_addr.addr)[2],
   //                                   ((u8_t *)&ip_netif.ip_addr.addr)[3]);
        }

        configPRINTF(("DHCP OK\r\n"));
  //      printf("DHCP OK\r\n");
    }

    return err;
}
