#ifndef _USRIO_H_
#define _USRIO_H_

//#include "../main/user_include.h"

#include "freertos/FreeRTOS.h"

#define GPIO_OUTPUT_IO_0    15
#define GPIO_OUTPUT_IO_1    16
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_IO_0     0
#define GPIO_INPUT_IO_1     5
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))

extern xQueueHandle gpio_evt_queue;

extern void usrGpioInit(void);

#endif