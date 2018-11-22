#include "esp_common.h"
#include "sw_wifi.h"
#include "debug_log.h"

#define AP_SSID "sunniwell_gt"
#define AP_PASSWD "sunniwell.1201"

static void wifi_handle_event_cb(System_Event_t *evt)
{
	switch(evt->event_id)
	{
		case EVENT_STAMODE_CONNECTED:
			SW_LOG_DEBUG("connect to ssid%s,channel	%d\n",evt->event_info.connected.ssid,
					evt->event_info.connected.channel);
			break;
		case EVENT_STAMODE_DISCONNECTED:
			SW_LOG_INFO("disconnect from ssid %s,reason %d\n",evt->event_info.disconnected.ssid,
					evt->event_info.disconnected.reason);
			break;
		case EVENT_STAMODE_AUTHMODE_CHANGE:
			SW_LOG_INFO("mode:%d->%d\n",evt->event_info.auth_change.old_mode,
					evt->event_info.auth_change.new_mode);
			break;
		case EVENT_STAMODE_GOT_IP:
			SW_LOG_INFO("ip:"IPSTR",mask:"IPSTR",gw:"IPSTR"\n",IP2STR(&evt->event_info.got_ip.ip),
					IP2STR(&evt->event_info.got_ip.mask),IP2STR(&evt->event_info.got_ip.gw));
			break;
		case EVENT_SOFTAPMODE_STACONNECTED:
			SW_LOG_INFO("station:"MACSTR"join,AID=%d\n",MAC2STR(evt->event_info.sta_connected.mac),
					evt->event_info.sta_connected.aid);
			break;
		case EVENT_SOFTAPMODE_STADISCONNECTED:
			SW_LOG_INFO("station:"MACSTR"leave,AID=%d\n",MAC2STR(evt->event_info.sta_disconnected.mac),
					evt->event_info.sta_disconnected.aid);
			break;
		default:
			break;
	}
}


static void station_mode(void)
{
	wifi_set_opmode(STATIONAP_MODE);
	struct station_config *config=(struct station_config*)zalloc(sizeof(struct	station_config));
	if(config == NULL)
	{
		SW_LOG_ERROR("zalloc config fail\n");
		return;
	}
	//config->bssid_set = 0;
	sprintf(config->ssid,AP_SSID);
	sprintf(config->password,AP_PASSWD);
	wifi_station_set_config(config);
	free(config);
	wifi_station_connect();
	//vTaskDelete(NULL);
}

int sw_wifi_init(int mode)
{
	if(mode == STATION_MODE)
		station_mode();
	//xTaskCreate(work_func,"wifi_config",    256,    NULL,   2,  NULL);
	wifi_set_event_handler_cb(wifi_handle_event_cb);
	return 0;
}
