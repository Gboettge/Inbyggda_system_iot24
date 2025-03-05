#include <stdio.h>
#include <freertos/FreeRTOS.h>
// #include "Button.h"
#include "Potentiometer.h"
#include "Binary_led.h"
#include "Analog_Led.h"
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
    

    xTaskCreate(
        aledSetOn,      // Function name of the task
        "Blink 1",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        NULL         // Task handle
    );
    
}
void aledSetOn(void* param){
    while(1){
        
    }
}