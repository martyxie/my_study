#ifndef __SW_WIFI_H__
#define __SW_WIFI_H__

#include "esp_sta.h"
typedef void (*wifi_conected_cb_t)(void);
int sw_wifi_init(int mode);

#endif
