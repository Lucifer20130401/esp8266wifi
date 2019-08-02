#ifndef _USR_TASK_H_
#define _USR_TASK_H_

#include "freertos/task.h"
#include "freertos/FreeRTOS.h"

extern const char *TAG;

void gpio_isr_handler(void *arg);

void gpio_task_example(void *arg);

void printLog(void *arg);
xTaskHandle handler_led_flash,handle_printTaskPiority;
void printTaskPriority(void *arg);
void ledFlash(void *arg);

#endif