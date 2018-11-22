#include "debug_log.h"
#include "esp_common.h"

void test_task_one(void *wplam)
{
	SW_LOG_DEBUG("hello,this my task one\n");
	int i = 0;
	while(1)
	{
		i++;
		SW_LOG_WARN("do task %d\n",i);
		//sleep(1);	
	}
	vTaskDelete(NULL);
}

void test_task_second(void *wplam)
{
	SW_LOG_DEBUG("hello,this my task secone\n");
	int i = 0;
	while(1)
	{
		i++;
		SW_LOG_ERROR("do task %d\n",i);
		//sleep(1);
		
	}
	vTaskDelete(NULL);
}


void  my_task_init(void)
{
	xTaskCreate(test_task_one,	"test_task_one",	256,	NULL,	2,	NULL);
	xTaskCreate(test_task_second,	"test_task_second",	256,	NULL,	2,	NULL);
	
}
