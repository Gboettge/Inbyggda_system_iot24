#include <stdio.h>
#include <math.h>
#include "Analog_Led.h"

float t = 0.0;

a_led_handle a_led_init(int pin, ledc_channel_t channel)
{
    a_led_handle newLED = pvPortMalloc (sizeof(a_led));
    newLED->sin = false;
    newLED->max_duty = MAX_DUTY;

    
    newLED->ledcTimerConfig.clk_cfg = LEDC_AUTO_CLK;
    newLED->ledcTimerConfig.deconfigure = false;
    newLED->ledcTimerConfig.duty_resolution = LEDC_TIMER_13_BIT;
    newLED->ledcTimerConfig.freq_hz = 1000;
    newLED->ledcTimerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->ledcTimerConfig.timer_num = LEDC_TIMER_0;
    ledc_fade_func_install(0);
    ledc_timer_config(&newLED->ledcTimerConfig);   
    if (ledc_timer_config(&newLED->ledcTimerConfig) != ESP_OK) {
        printf("LEDC timer config failed!\n");
        free(newLED);
        return NULL;
    }      
    newLED->ledcChannelConfig.gpio_num = pin;
    newLED->ledcChannelConfig.channel = LEDC_CHANNEL_0;
    newLED->ledcChannelConfig.duty = 0;
    newLED->ledcChannelConfig.flags.output_invert = 0;
    newLED->ledcChannelConfig.hpoint = 0;
    newLED->ledcChannelConfig.intr_type = LEDC_INTR_DISABLE;
    newLED->ledcChannelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->ledcChannelConfig.sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD;
    newLED->ledcChannelConfig.timer_sel = LEDC_TIMER_0;
    
    ledc_channel_config(&newLED->ledcChannelConfig);
   
    if (ledc_channel_config(&newLED->ledcChannelConfig) != ESP_OK) {
        printf("LEDC channel config failed!\n");
        free(newLED);
        return NULL;
    }

    return newLED;     
}

void a_led_update(a_led_handle led){
    if (led->sin == true)
    {
        float sin_value = sinf(t); // sinf(t) returns -1 to 1
        int duty = (int)(sin_value * (MAX_DUTY/2)) + (MAX_DUTY/2);
        a_led_setLed(led, duty);
        printf("duty: %d\n", duty);
        t += (2*M_PI) / led->period; // Increment t based on the period
        return;
    }
    if (led->duty == 50)
    {
        return;/* code */
    }
    
    printf("duty: %ld", led->duty);
    led->duty = led->duty - 50;
    if(led->duty < 200){
        led->duty = 50;
    }
    ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, led->duty);
    ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
    // if (led->previousDuty != led->duty)
    //     {
    //         led->previousDuty = led->duty;
    //         ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, led->duty, 0);
    //     }
   // ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, led->ledcChannelConfig.duty);
   // ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
}

void a_led_setLed(a_led_handle led, uint32_t duty)
{
    if (led == NULL) {
        printf("LED handle is NULL!\n");
        return;
    }
    if (duty > 5000){
        duty = 5000;
    }
    led->duty = duty;
    ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, duty);
    ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
    //ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, led->duty, 0);
}

void a_led_sin(a_led_handle led, int period){
    led->sin = true;
    led->period = period;
}