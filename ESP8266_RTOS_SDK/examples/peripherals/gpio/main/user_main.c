/* gpio example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/



#include "user_include.h"

const char *TAG = "wifi & gpio";


void app_main(void)
{

    printf("hello world!\n");

    usrGpioInit();

    usrwifiInit();
    
    xTaskCreate(gpio_task_example, "gpio_task_example", 1024, NULL, 10, NULL);

    xTaskCreate(printLog,"printthelogforatest",1024,NULL,10,NULL);

    xTaskCreate(ledFlash,"led flash",1024,NULL,10,handler_led_flash);
    
    xTaskCreate(printTaskPriority,"print priority of a task",2048,NULL,10,handle_printTaskPiority);
    
    xTaskCreate(echo_task, "uart_echo_task", 1024, NULL, 10, NULL);

    
    
}


