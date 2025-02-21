#include "driver/ledc.h" 
//#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#define MAX_DUTY 4096

typedef struct
{
    bool red_sin;
    float red_t;
    int red_period;
    uint32_t red_max_duty;
    uint32_t red_duty;
    uint32_t red_previousDuty;
    // ledc_timer_config_t red_ledcTimerConfig;
    // ledc_channel_config_t red_ledcChannelConfig;

    bool green_sin;
    float green_t;
    int green_period;
    uint32_t green_max_duty;
    uint32_t green_duty;
    uint32_t green_previousDuty;
    // ledc_timer_config_t green_ledcTimerConfig;
    // ledc_channel_config_t green_ledcChannelConfig;

    bool blue_sin;
    float blue_t;
    int blue_period;
    uint32_t blue_max_duty;
    uint32_t blue_duty;
    uint32_t blue_previousDuty;
    // ledc_timer_config_t blue_ledcTimerConfig;
    // ledc_channel_config_t blue_ledcChannelConfig;
} a_led;

typedef a_led* a_led_handle;

a_led_handle a_led_init(int red_pin, int green_pin, int blue_pin);

void a_led_update(a_led_handle led);

void a_led_setLed(a_led_handle led, uint32_t red_duty, uint32_t green_duty, uint32_t blue_duty); //duty 0-255

void a_led_sin(a_led_handle led, int period);

void a_led_destroy(a_led_handle *led);
