#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

// #include "Button.h"
#include "Potentiometer.h"
#include "Binary_led.h"
#include "Analog_Led.h"

const char * TAG = "Main";

void aledSetOn(void* param);

a_led_handle aled;
pot_handle adc;
TickType_t currentTick;
TickType_t elapseTime;
void app_main(void)
{
    adc = potentiometer_init(0, 1);
    aled = a_led_init(4, 0, 0, 0);
    a_led_sin(aled, 200);
    
    ESP_LOGI(TAG, "app_main STARTING");

    xTaskCreate(
        aledSetOn,      // Function name of the task
        "Task 1",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        NULL         // Task handle
    );
    
}
void aledSetOn(void* param){
    ESP_LOGI(TAG, "Task 1 function running");
    int counter = param
    while (true)
    {
        ESP_LOGI(TAG, "counter: %d", *counter++);
    }
    ESP_LOGI(TAG, "Task 1 function returning");
    vTaskDelete(NULL);
}