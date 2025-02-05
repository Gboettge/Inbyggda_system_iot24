#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h" 
#define BTN_PRESS GPIO_NUM_5

void app_main(void)
{
gpio_set_direction(BTN_PRESS, GPIO_MODE_INPUT);
}