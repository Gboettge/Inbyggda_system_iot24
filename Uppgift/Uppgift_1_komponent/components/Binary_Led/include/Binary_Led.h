#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

typedef enum{
    STATE_ON,
    STATE_OFF,
    BLINK_ON,
    BLINK_OFF
}b_led_state_e;

typedef struct{
    gpio_config_t gpio_config;
    gpio_num_t pin;
    int level;
    int milisecOn;
    int milisecOff;
    b_led_state_e current_state;
    b_led_state_e next_state;
    
}Bin_LED;

typedef Bin_LED* Bin_LED_handle;

Bin_LED_handle init(int pin);

void update(Bin_LED_handle LED);

void setLed(Bin_LED_handle LED, int value);

void blink(Bin_LED_handle LED, int milisecOn, int milisecOff);

