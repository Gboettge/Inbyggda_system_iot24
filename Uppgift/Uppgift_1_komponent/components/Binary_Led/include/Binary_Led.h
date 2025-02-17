#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

typedef enum{
    LIGHT_OFF,
    LIGHT_ON
}b_led_light_e;

typedef enum{
    OFF,
    ON,
    BLINK_ON,
    BLINK_OFF
}b_led_state_e;

typedef struct{
    
    gpio_num_t pin;
    b_led_light_e light_mode;
    int level;
    int milisecOn;
    int milisecOff;
    bool ledON;
    b_led_state_e current_state;
    b_led_state_e next_state;
    b_led_state_e previous_state;
    TickType_t tick_elapse;
    
}Bin_LED;

typedef Bin_LED* Bin_LED_handle;

Bin_LED_handle b_led_init(int pin,b_led_light_e mode, bool blink);

void b_led_update(Bin_LED_handle LED);

void b_led_setLed(Bin_LED_handle LED, b_led_light_e light_mode);

void b_led_blink(Bin_LED_handle LED, int milisecOn, int milisecOff);

void b_led_destroy(Bin_LED_handle *led);
