#include <stdio.h>
#include <math.h>
#include "Analog_Led.h"



a_led_handle a_led_init(int pin, ledc_channel_t channel, ledc_timer_t timer, int hpoint)
{
    a_led_handle newLED = pvPortMalloc (sizeof(a_led));
    newLED->sin = false;
    newLED->max_duty = MAX_DUTY;
    newLED->t = 0.0;

    
    newLED->ledcTimerConfig.clk_cfg = LEDC_AUTO_CLK;
    newLED->ledcTimerConfig.deconfigure = false;
    newLED->ledcTimerConfig.duty_resolution = LEDC_TIMER_12_BIT;
    newLED->ledcTimerConfig.freq_hz = 4000;
    newLED->ledcTimerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->ledcTimerConfig.timer_num = timer;
    
    ledc_timer_config(&newLED->ledcTimerConfig);   
    
    newLED->ledcChannelConfig.gpio_num = pin;
    newLED->ledcChannelConfig.channel = channel;
    newLED->ledcChannelConfig.duty = 0;
    newLED->ledcChannelConfig.flags.output_invert = 0;
    newLED->ledcChannelConfig.hpoint = hpoint;
    newLED->ledcChannelConfig.intr_type = LEDC_INTR_DISABLE;
    newLED->ledcChannelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->ledcChannelConfig.sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD;
    newLED->ledcChannelConfig.timer_sel = timer;
    
    ledc_channel_config(&newLED->ledcChannelConfig);
   
    return newLED;     
}

void a_led_update(a_led_handle led){
    if (led->sin == true)
    {
        float sin_value = sinf(led->t); // returns -1 to 1
        int duty = (int)(sin_value * (MAX_DUTY/2)) + (MAX_DUTY/2);
        led->duty = duty;
        ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, led->duty);
        ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
        //printf("duty: %d\n", duty); //
        led->t += (2*M_PI) / led->period; 
        return;
    }
    if (led->previousDuty == led->duty)
    {
        return;
    }
    
    if (led->previousDuty != led->duty)
    {
        led->previousDuty = led->duty;
        ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, led->duty);
        ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
    }
    else if (led == NULL) {
        printf("LED handle is NULL!\n");
        return;
    }
   
}

void a_led_setLed(a_led_handle led, uint32_t duty)
{
    if (duty > MAX_DUTY){
        duty = MAX_DUTY;
    }
    led->duty = duty;
    led->sin = false;
}

void a_led_sin(a_led_handle led, int period){
    led->sin = true;
    led->period = period;
}
void a_led_destroy(a_led_handle *led){
    vPortFree(led);
}