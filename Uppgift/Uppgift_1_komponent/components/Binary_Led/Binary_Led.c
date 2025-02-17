#include <stdio.h>
#include "Binary_Led.h"

Bin_LED_handle b_led_init(int pin, b_led_light_e light_mode, bool blink){
    Bin_LED_handle newLED = pvPortMalloc (sizeof(Bin_LED));
   

    newLED->pin = pin;
    newLED->level = 0;
    newLED->milisecOn = 0;
    newLED->milisecOff = 0;
    newLED->light_mode = light_mode;
    newLED->current_state = ON;
    newLED->ledON = blink;
    newLED->tick_elapse = 0;

    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    return newLED;     
}

void b_led_update(Bin_LED_handle LED)
{
    TickType_t current_tick = xTaskGetTickCount();
    switch (LED->current_state)
    {
    case ON:
        if(LED->light_mode == LIGHT_ON){
            gpio_set_level(LED->pin, LIGHT_ON);
        }
        LED->next_state = OFF;
        //LED->light_mode = LIGHT_ON;
        break;

    case OFF:
        if(LED->light_mode == LIGHT_OFF){
            gpio_set_level(LED->pin, LIGHT_OFF);
        }
        LED->next_state = ON;
        //LED->light_mode = LIGHT_OFF;
        if(LED->ledON == true){
            printf("ledON == true\n");
            LED->next_state = BLINK_ON;
        }
        break;

    case BLINK_ON:
        
        if(current_tick - LED->tick_elapse >= pdMS_TO_TICKS(LED->milisecOn))
        {
            printf("\n\n");
            LED->next_state = BLINK_OFF;
            LED->tick_elapse = current_tick;
            //LED->tick_elapse = 0;
        }
        else{
            LED->next_state = BLINK_ON;
            
        }
        
        gpio_set_level(LED->pin, 1);
        break;
    case BLINK_OFF:
        if(current_tick - LED->tick_elapse >= pdMS_TO_TICKS(LED->milisecOff))
        {
        printf("\n\n");
        LED->next_state = BLINK_ON;
        LED->tick_elapse = current_tick;
        //LED->tick_elapse = 0;
        }
        else{
            LED->next_state = BLINK_OFF;
        }
        gpio_set_level(LED->pin, 0);
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

void b_led_setLed(Bin_LED_handle LED, b_led_light_e light_mode){
    
    LED->light_mode = light_mode;
    if(LIGHT_ON){
        LED->current_state = ON;
    }
    else{
        LED->current_state = OFF;
    }
}

void b_led_blink(Bin_LED_handle LED, int milisecOn, int milisecOff){
    LED->current_state = BLINK_ON;
    LED->milisecOn = milisecOn;
    LED->milisecOff = milisecOff;
}