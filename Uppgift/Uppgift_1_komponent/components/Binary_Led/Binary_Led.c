#include <stdio.h>
#include "Binary_Led.h"

Bin_LED_handle b_led_init(int pin){
    Bin_LED_handle newLED = pvPortMalloc (sizeof(Bin_LED));
   

    newLED->pin = pin;
    newLED->level = 0;
    newLED->milisecOn = 0;
    newLED->milisecOff = 0;
    newLED->value = 0;
    newLED->current_state = ON;

    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    return newLED;     
}

void b_led_update(Bin_LED_handle LED)
{
    switch (LED->current_state)
    {

    case ON:
        LED->next_state = OFF;
        gpio_set_level(LED->pin, 1);
        break;
    case OFF:
        LED->next_state = ON;
        gpio_set_level(LED->pin, 0);
        break;
    case BLINK_ON:

        break;
    case BLINK_OFF:

        break;
    default:
        printf("error %d\n", LED->current_state);
        break;
    }
    if(LED->next_state != LED->current_state){
         printf("%d -> %d\n", LED->current_state, LED->next_state);
    }
    LED->previous_state = LED->current_state;
    LED->current_state = LED->next_state;
}

void b_led_setLed(Bin_LED_handle LED, int value){
    LED->value = value;
}

void b_led_blink(Bin_LED_handle LED, int milisecOn, int milisecOff){
    LED->milisecOn = milisecOn;
    LED->milisecOff = milisecOff;
}