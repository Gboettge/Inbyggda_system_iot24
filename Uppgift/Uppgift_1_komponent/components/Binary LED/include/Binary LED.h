#include "driver/ledc.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

typedef struct{
    int pin;
    int duty;
    int previousDuty;
    ledc_timer_config_t ledcTimerConfig;
    ledc_channel_config_t ledcChannelConfig;
}Bin_LED;

typedef Bin_LED* Bin_LED_handle;

Bin_LED_handle init(int pin);

void update(Bin_LED_handle LED);

void setLed(Bin_LED_handle LED, int value);

void blink(Bin_LED_handle LED, int milisecOn, int milisecOff);