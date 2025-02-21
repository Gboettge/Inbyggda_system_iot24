#include <stdio.h>
#include <math.h>
#include "RGB_LED.h"




a_led_handle a_led_init(int red_pin, int green_pin, int blue_pin)
{
    a_led_handle newLED = pvPortMalloc (sizeof(a_led));
    newLED->red_sin = false;
    newLED->red_max_duty = MAX_DUTY;
    newLED->red_t = 0.0;
    
    newLED->red_ledcTimerConfig.clk_cfg = LEDC_AUTO_CLK;
    newLED->red_ledcTimerConfig.deconfigure = false;
    newLED->red_ledcTimerConfig.duty_resolution = LEDC_TIMER_12_BIT;
    newLED->red_ledcTimerConfig.freq_hz = 4000;
    newLED->red_ledcTimerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->red_ledcTimerConfig.timer_num = 0; //timer;
    ledc_timer_config(&newLED->red_ledcTimerConfig);   
    newLED->red_ledcChannelConfig.gpio_num = red_pin;
    newLED->red_ledcChannelConfig.channel = 0; //channel;
    newLED->red_ledcChannelConfig.duty = 0;
    newLED->red_ledcChannelConfig.flags.output_invert = 0;
    newLED->red_ledcChannelConfig.hpoint = 0;       //hpoint;
    newLED->red_ledcChannelConfig.intr_type = LEDC_INTR_DISABLE;
    newLED->red_ledcChannelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->red_ledcChannelConfig.sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD;
    newLED->red_ledcChannelConfig.timer_sel = 0;//timer;
    ledc_channel_config(&newLED->red_ledcChannelConfig);
    

    newLED->green_sin = false;
    newLED->green_max_duty = MAX_DUTY;
    newLED->green_t = 0.0;

    newLED->green_ledcTimerConfig.clk_cfg = LEDC_AUTO_CLK;
    newLED->green_ledcTimerConfig.deconfigure = false;
    newLED->green_ledcTimerConfig.duty_resolution = LEDC_TIMER_12_BIT;
    newLED->green_ledcTimerConfig.freq_hz = 4000;
    newLED->green_ledcTimerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->green_ledcTimerConfig.timer_num = 0;//timer;
    ledc_timer_config(&newLED->green_ledcTimerConfig);   
    newLED->green_ledcChannelConfig.gpio_num = green_pin;
    newLED->green_ledcChannelConfig.channel = 1;//channel;
    newLED->green_ledcChannelConfig.duty = 0;
    newLED->green_ledcChannelConfig.flags.output_invert = 0;
    newLED->green_ledcChannelConfig.hpoint = 1;//hpoint;
    newLED->green_ledcChannelConfig.intr_type = LEDC_INTR_DISABLE;
    newLED->green_ledcChannelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->green_ledcChannelConfig.sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD;
    newLED->green_ledcChannelConfig.timer_sel = 0;//timer;
    ledc_channel_config(&newLED->green_ledcChannelConfig);
    
    newLED->blue_sin = false;
    newLED->blue_max_duty = MAX_DUTY;
    newLED->blue_t = 0.0;

    newLED->blue_ledcTimerConfig.clk_cfg = LEDC_AUTO_CLK;
    newLED->blue_ledcTimerConfig.deconfigure = false;
    newLED->blue_ledcTimerConfig.duty_resolution = LEDC_TIMER_12_BIT;
    newLED->blue_ledcTimerConfig.freq_hz = 4000;
    newLED->blue_ledcTimerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->blue_ledcTimerConfig.timer_num = 0;//timer;
    ledc_timer_config(&newLED->blue_ledcTimerConfig);   
    newLED->blue_ledcChannelConfig.gpio_num = blue_pin;//pin;
    newLED->blue_ledcChannelConfig.channel = 2;//channel;
    newLED->blue_ledcChannelConfig.duty = 0;
    newLED->blue_ledcChannelConfig.flags.output_invert = 0;
    newLED->blue_ledcChannelConfig.hpoint = 2;//hpoint;
    newLED->blue_ledcChannelConfig.intr_type = LEDC_INTR_DISABLE;
    newLED->blue_ledcChannelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->blue_ledcChannelConfig.sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD;
    newLED->blue_ledcChannelConfig.timer_sel = 0;//timer;
    ledc_channel_config(&newLED->blue_ledcChannelConfig);
    return newLED;     
}

void a_led_update(a_led_handle led){
    // if (led->sin == true)
    // {
    //     float sin_value = sinf(led->t); // returns -1 to 1
    //     int duty = (int)(sin_value * (MAX_DUTY/2)) + (MAX_DUTY/2);
    //     led->duty = duty;
    //     ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, led->duty);
    //     ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
    //     //printf("duty: %d\n", duty); //
    //     led->t += (2*M_PI) / led->period; 
    //     return;
    // }
    // if (led->previousDuty == led->duty)
    // {
    //     return;
    // }
    
    // if (led->previousDuty != led->duty)
    // {
    //     led->previousDuty = led->duty;
    //     ledc_set_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel, led->duty);
    //     ledc_update_duty(led->ledcChannelConfig.speed_mode, led->ledcChannelConfig.channel);
    // }
    // else if (led == NULL) {
    //     printf("LED handle is NULL!\n");
    //     return;
    // }

    int notChange = 0;
    if (led->red_previousDuty == led->red_duty)
    {
        notChange++;
    }
    if (led->green_previousDuty == led->green_duty)
    {
        notChange++;
    }
    if (led->blue_previousDuty == led->blue_duty)
    {
        notChange++;
    }
    if (notChange == 3){
        return;
    }

    if (led->red_previousDuty != led->red_duty)
    {
        led->red_previousDuty = led->red_duty;
        ledc_set_duty(led->red_ledcChannelConfig.speed_mode, led->red_ledcChannelConfig.channel, led->red_duty);
        ledc_update_duty(led->red_ledcChannelConfig.speed_mode, led->red_ledcChannelConfig.channel);
    }

    if (led->green_previousDuty != led->green_duty)
    {
        led->green_previousDuty = led->green_duty;
        ledc_set_duty(led->green_ledcChannelConfig.speed_mode, led->green_ledcChannelConfig.channel, led->green_duty);
        ledc_update_duty(led->green_ledcChannelConfig.speed_mode, led->green_ledcChannelConfig.channel);
    }
    if (led->blue_previousDuty != led->blue_duty)
    {
        led->blue_previousDuty = led->blue_duty;
        ledc_set_duty(led->blue_ledcChannelConfig.speed_mode, led->blue_ledcChannelConfig.channel, led->red_duty);
        ledc_update_duty(led->blue_ledcChannelConfig.speed_mode, led->blue_ledcChannelConfig.channel);
    }
    else if (led == NULL) {
        printf("LED handle is NULL!\n");
         return;
    }
}

void a_led_setLed(a_led_handle led, uint32_t red_duty, uint32_t green_duty, uint32_t blue_duty) //duty 0-255
{   
    int newDuty = red_duty * 3;
    if (newDuty > MAX_DUTY){
        newDuty = MAX_DUTY;
    }
    led->red_duty = newDuty;
    led->red_sin = false;

    newDuty = green_duty * 3;
    if (newDuty > MAX_DUTY){
        newDuty = MAX_DUTY;
    }
    led->green_duty = newDuty;
    led->green_sin = false;

    newDuty = blue_duty * 16;
    if (newDuty > MAX_DUTY){
        newDuty = MAX_DUTY;
    }
    led->blue_duty = newDuty;
    led->blue_sin = false;

    /*
    int newDuty = duty * 16;
    if (newDuty > MAX_DUTY){
        newDuty = MAX_DUTY;
    }
    led->duty = newDuty;
    led->sin = false;
    */
}

void a_led_sin(a_led_handle led, int period){
    // led->sin = true;
    // led->period = period;
}
void a_led_destroy(a_led_handle *led){
    vPortFree(led);
}