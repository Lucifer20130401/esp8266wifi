#ifndef _USER_INCLUDE_H_
#define _USER_INCLUDE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"


#include "driver/uart.h"

#include <string.h>
#include <stdlib.h>
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"

#include "rom/ets_sys.h"
#include "esp_log.h"
#include "nvs_flash.h"



#include "../components/io/usrio.h"
#include "../components/usr_task/usr_task.h"
#include "../components/usrUart/usruart.h"
#include "../components/usrwifi/usrwifi.h"


#endif