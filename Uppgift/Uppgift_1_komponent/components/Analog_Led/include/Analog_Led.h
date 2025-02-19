#include "driver/ledc.h" 
//#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#define MAX_DUTY 4096

typedef struct{
    bool sin;
    float t;
    int period;
    uint32_t max_duty;
    uint32_t duty;
    uint32_t previousDuty;
    ledc_timer_config_t ledcTimerConfig;
    ledc_channel_config_t ledcChannelConfig;
}a_led;

typedef a_led* a_led_handle;

a_led_handle a_led_init(int pin, ledc_channel_t channel, ledc_timer_t timer);

void a_led_update(a_led_handle led);

void a_led_setLed(a_led_handle led, uint32_t duty);

void a_led_sin(a_led_handle led, int period);

void a_led_destroy(a_led_handle *led);
