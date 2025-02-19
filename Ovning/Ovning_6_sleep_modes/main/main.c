#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Binary_led.h"
#include "Analog_Led.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#define ONE_SEC 1000000


button_handle btn;
void myFunc()
{
   
}
void app_main(void)
{
    btn = button_init(23, GPIO_PULLDOWN);
    button_setOnPressed(btn, myFunc);
    //esp_err_t esp_sleep_enable_gpio_wakeup(void)
    int counter = 0;
    while(1)
    {
        esp_sleep_enable_timer_wakeup(ONE_SEC * 10 - 50000);
        if(counter >= 10)
        {
            esp_sleep_enable_timer_wakeup(ONE_SEC *10);
            esp_deep_sleep_start();
            counter = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(50));
        esp_light_sleep_start();
        counter ++;
        printf("%d seconds passed\n", counter);
    }
}