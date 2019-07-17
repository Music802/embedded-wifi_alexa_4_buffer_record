#include "wwd.h"
#include "wwd_wiced.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AP_SSID             "VSG1"
#define AP_PASS             "vsvs123123"
#define AP_SEC              WICED_SECURITY_WPA2_MIXED_PSK
#define FIXED_SSID 1

wwd_result_t wwd_wifi_leave( wwd_interface_t interface );
wiced_result_t register_link_events(wiced_security_t security, void *);
void pp_dhcp_stop();
/*******************************************************************************
 * Code
 ******************************************************************************/

void test_join(void);
static const wiced_ssid_t pp_ap_ssid =
{
    .length = sizeof(AP_SSID)-1,
    .value  = AP_SSID,
};

void wifi_link_events_callback(int event)
{
    //Note that this event is called from WWD thread.
    //No processing should be done from this callback.
    //This function should be used to just to wakeup
    //Link Manager thread.
    if(event)
        PRINTF("Link UP\n");
    else 
        PRINTF("Link Down\n");
}

void test_join(void)
{
    int result;

    PRINTF("Joining : " AP_SSID "\n");
    if ( wwd_wifi_join( &pp_ap_ssid, AP_SEC, (uint8_t*) AP_PASS, sizeof( AP_PASS ) - 1, NULL, WWD_STA_INTERFACE ) != WWD_SUCCESS )
    {
        PRINTF("Failed to join  : " AP_SSID " \n");
        return;
    }
    else
        PRINTF("Successfully joined : " AP_SSID "\n");

    result = register_link_events(AP_SEC, &wifi_link_events_callback);
    if(result != WWD_SUCCESS)
    {   
        WPRINT_WWD_INFO(("Register Link Events failed : %d\n",result));
        return;
    }

    return;
}

void test_leave()
{
    pp_dhcp_stop();
    wwd_wifi_leave(WWD_STA_INTERFACE);
}

