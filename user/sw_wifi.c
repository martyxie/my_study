#include "esp_common.h"
#include "sw_wifi.h"
#include "debug_log.h"

#define AP_SSID "sunniwell_gt"
#define AP_PASSWD "sunniwell.1201"

static void staton_mode(void)
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
	void *work_func = NULL;
	if(mode == STATION_MODE)
		work_func = staton_mode;
	staton_mode();
	//xTaskCreate(work_func,"wifi_config",    256,    NULL,   2,  NULL);
	return 0;
}
