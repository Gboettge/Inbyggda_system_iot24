#include <stdio.h>
#include "RGB_LED.h"
#include "Button.h"
#include "Potentiometer.h"

a_led_handle RGB;
button_handle btn1;
button_handle btn2;
button_handle btn3;
pot_handle adc;

void adcValueToRed();
void adcValueToGreen();
void adcValueToBlue();

void app_main(void)
{
    RGB = a_led_init(2, 3, 4);
    // btn1 = button_init(18, GPIO_PULLDOWN);
    // btn2 = button_init(20, GPIO_PULLDOWN);
    // btn3 = button_init(19, GPIO_PULLDOWN);
    adc = potentiometer_init(ADC_UNIT_1, ADC_CHANNEL_1);
    
    a_led_setLed(RGB, 52, 213, 235);
    // button_setOnPressed(btn1, adcValueToRed);
    // button_setOnPressed(btn2, adcValueToGreen);
    // button_setOnPressed(btn3, adcValueToBlue);
    
    //a_led_sin(red, 300);
    //a_led_sin(green, 600);
    //a_led_sin(blue, 600);
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(20));
        a_led_update(RGB);
        // button_update(btn1);
        // button_update(btn2);
        // button_update(btn3);
        // pot_update(adc);
    }
    
}
void adcValueToRed(){
    int value = pot_get_value(adc);
    a_led_setLed(RGB, value, 0, 0);
}
void adcValueToGreen(){
    int value = pot_get_value(adc);
    a_led_setLed(RGB, 0, value, 0);
}
void adcValueToBlue(){
    int value = pot_get_value(adc);
    a_led_setLed(RGB, 0, 0, value);
}