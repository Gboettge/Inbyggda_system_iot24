#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Binary_Led.h"

button_handle btn1;
button_handle btn2;
button_handle btn3;
pot_handle adc;
Bin_LED_handle b_Led;

void app_main(void)
{
    printf("Starting main\n");
    adc = potentiometer_init(ADC_UNIT_1, ADC_CHANNEL_1);
    btn1 = button_init(GPIO_NUM_2, GPIO_PULLDOWN);
    btn2 = button_init(GPIO_NUM_3, GPIO_PULLDOWN);
    btn3 = button_init(GPIO_NUM_23, GPIO_PULLUP);
    b_Led = b_led_init(GPIO_NUM_15, LIGHT_OFF, false);

    button_setOnPressed(btn1, button_print_press_num);
    button_setOnPressed(btn2, button_print_num_x_ten);
    button_setOnReleased(btn1, button_print_released);
    button_setOnReleased(btn2, button_print_released);
    pot_setOnThreshold(adc, 3000, pot_printThresholdReach);
    // b_led_setLed(bLed, LIGHT_ON);
    b_led_blink(b_Led, 500, 3000);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(200));
        pot_update(adc);
        button_update(btn1);
        button_update(btn2);
        button_update(btn3);
        b_led_update(b_Led);
    }
    button_destroy(&btn1);
    button_destroy(&btn2);
    button_destroy(&btn3);
    pot_destroy(&adc);
    b_led_destroy(&b_Led);
}