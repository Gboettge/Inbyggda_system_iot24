#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

typedef enum{
    ON,
    OFF,
    BLINK_ON,
    BLINK_OFF
}b_led_state_e;

typedef struct{
    
    gpio_num_t pin;
    int value;
    int level;
    int milisecOn;
    int milisecOff;
    bool ledON;
    b_led_state_e current_state;
    b_led_state_e next_state;
    b_led_state_e previous_state;
    
}Bin_LED;

typedef Bin_LED* Bin_LED_handle;

Bin_LED_handle b_led_init(int pin);

void b_led_update(Bin_LED_handle LED);

void b_led_setLed(Bin_LED_handle LED, int value);

void b_led_blink(Bin_LED_handle LED, int milisecOn, int milisecOff);

