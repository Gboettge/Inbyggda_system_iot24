#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Binary_Led.h"

button_handle btn1;
button_handle btn2;
button_handle btn3;
pot_handle adc;
Bin_LED_handle bLed;

void app_main(void)
{
    printf("Starting main\n");
    adc = potentiometer_init(ADC_UNIT_1, ADC_CHANNEL_1);
    btn1 = button_init(GPIO_NUM_15, GPIO_PULLUP);
    btn2 = button_init(GPIO_NUM_5, GPIO_PULLDOWN);
    btn3 = button_init(GPIO_NUM_20, GPIO_PULLDOWN);
    bLed = b_led_init(GPIO_NUM_14);
    
    button_setOnPressed(btn1, button_print_press_num);
    button_setOnPressed(btn2, button_print_num_x_ten);
    button_setOnReleased(btn1, button_print_released);
    button_setOnReleased(btn2, button_print_released);
    pot_setOnThreshold(adc, 3000, pot_printThresholdReach);
    
     while(1)
     {
         vTaskDelay(pdMS_TO_TICKS(200));
         pot_update(adc);
         button_update(btn1);
         button_update(btn2);
         button_update(btn3);
         b_led_update(bLed);


     }
     void button_destroy(button_handle *btn1);
     void button_destroy(button_handle *btn2);
     void button_destroy(button_handle *btn3);
}