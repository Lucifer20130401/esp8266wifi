#include "../../main/user_include.h"

void gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void gpio_task_example(void *arg)
{
    uint32_t io_num;

    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY))
        {
            ESP_LOGI(TAG, "GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}

void printLog(void *arg)
{
    unsigned int i = 0;
    for (;;) //(1/* condition */)
    {
        i++;
        ESP_LOGI(TAG, "i = %d", i);
        printf("Hello vincent, this is a foo test!\ni=%d\n\n\n", i);
        vTaskDelay(8000 / portTICK_RATE_MS);
        // gpio_set_level(GPIO_OUTPUT_IO_0, i % 2);
        // gpio_set_level(GPIO_OUTPUT_IO_1, i % 2);

        //printf("hello Vincent!\n");
    }
}

xTaskHandle handler_led_flash, handle_printTaskPiority;

void printTaskPriority(void *arg)
{
    TickType_t nowTime = xTaskGetTickCount();
    TickType_t const thenTime = 16000;
    UBaseType_t p = 0;
    for (;;)
    {
        vTaskDelayUntil(&nowTime, thenTime / portTICK_RATE_MS);
        p = uxTaskPriorityGet(handler_led_flash);
        printf("the taks priority = %ld\n", p);
    }
}

void ledFlash(void *arg)
{
    uint16_t i = 0;
    for (;;)
    {
        i++;
        vTaskDelay(200 / portTICK_RATE_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0, i % 2);
        gpio_set_level(GPIO_OUTPUT_IO_1, i % 2);
    }
}
