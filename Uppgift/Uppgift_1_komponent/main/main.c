#include <stdio.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Binary_Led.h"
#include "Analog_Led.h"

button_handle btn1;
button_handle btn2;
button_handle btn3;
pot_handle adc;
// b_led_handle b_Led;
a_led_handle red;
a_led_handle green;
a_led_handle blue;
int value = 0;
int green_value = 0;
int blue_value = 0;

void changeRed();
void changeGreen();
void changeBlue();

void app_main(void)
{

    printf("Starting main\n");
    adc = potentiometer_init(ADC_UNIT_1, ADC_CHANNEL_1);
    btn1 = button_init(GPIO_NUM_18, GPIO_PULLDOWN);
    btn2 = button_init(GPIO_NUM_20, GPIO_PULLDOWN);
    btn3 = button_init(GPIO_NUM_21, GPIO_PULLDOWN);
    
    // b_Led = b_led_init(GPIO_NUM_9, LIGHT_OFF, false);
    red = a_led_init(2,0,0);
    green = a_led_init(3,1,0);
    blue = a_led_init(4,2,0);
    
    button_setOnPressed(btn1, changeRed);
    button_setOnPressed(btn2, changeGreen);
    button_setOnPressed(btn3, changeBlue);
    // button_setOnPressed(btn2, button_print_num_x_ten);
    // button_setOnReleased(btn1, button_print_released);
    // button_setOnReleased(btn2, button_print_released);
    pot_setOnThreshold(adc, 3000, pot_printThresholdReach);
    
    // b_led_setled(b_Led, LIGHT_ON);
    //b_led_blink(b_Led, 50, 550);

    
    a_led_setLed(blue, 0);
    a_led_setLed(red, 0);
    a_led_setLed(green, 0);

    a_led_sin(red, 300); //
    a_led_sin(green, 400); //
    //a_led_sin(blue, 300);
    
    
    int adc_value;//
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(20));
        pot_update(adc);
        button_update(btn1);
        button_update(btn2);
        button_update(btn3);
        // b_led_update(b_Led);
        a_led_update(red);
        a_led_update(green);
        a_led_update(blue);

        
        // adc_value = pot_get_value(adc);//
        // if (adc_value <80){
        //     adc_value = 0;
        //     printf("value:%d\n", adc_value);
        // }
        // a_led_setLed(blue, adc_value); //
        
    }
    // button_destroy(&btn1);
    // button_destroy(&btn2);
    // button_destroy(&btn3);
    // pot_destroy(&adc);
    // b_led_destroy(&b_Led);
    a_led_destroy(&red);
    
}


void changeRed(){
    value += 400;
    if (value > 4050){
        
        value = 0;
        
    }
    printf("red val: %d\n", value);
    a_led_setLed(red, value); //
}

void changeGreen(){
    green_value += 400;
    if (green_value > 4050){
        
        green_value = 0;
        
    }
    printf("green val: %d\n", green_value);
    a_led_setLed(green, green_value); //
}
void changeBlue(){
    blue_value += 400;
    if (blue_value > 4050){

        blue_value = 0;

    }
    printf("blue val: %d\n", blue_value);
    a_led_setLed(blue, blue_value); //
}