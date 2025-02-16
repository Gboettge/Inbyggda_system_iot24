#include <stdio.h>
#include "Binary LED.h"

Bin_LED_handle init(int pin){
    Bin_LED_handle newLED = pvPortMalloc (sizeof(Bin_LED));
    newLED->pin = pin;
    newLED->duty = 0; //
    newLED->previousDuty = 0;

    newLED->ledcChannelConfig.channel = LEDC_CHANNEL_0;
    newLED->ledcChannelConfig.duty = 0;
    newLED->ledcChannelConfig.flags.output_invert = 0;
    newLED->ledcChannelConfig.gpio_num = pin;
    newLED->ledcChannelConfig.hpoint = 0;
    newLED->ledcChannelConfig.intr_type = LEDC_INTR_DISABLE;
    newLED->ledcChannelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->ledcChannelConfig.timer_sel = LEDC_TIMER_0;

    newLED->ledcTimerConfig.clk_cfg = LEDC_AUTO_CLK;
    newLED->ledcTimerConfig.deconfigure = false;
    newLED->ledcTimerConfig.duty_resolution = LEDC_TIMER_12_BIT;
    newLED->ledcTimerConfig.freq_hz = 1000;
    newLED->ledcTimerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    newLED->ledcTimerConfig.timer_num = LEDC_TIMER_0;         
    return newLED;     
}

Bin_LED_handle init(int pin){

}

void update(Bin_LED_handle LED){

}

void setLed(Bin_LED_handle LED, int value){

}

void blink(Bin_LED_handle LED, int milisecOn, int milisecOff){
    
}