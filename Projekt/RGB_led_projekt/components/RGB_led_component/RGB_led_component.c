#include <stdio.h>
#include "RGB_led_component.h"

RGB_handle rgb_init(){
    RGB_handle newRGB = pvPortMalloc(sizeof(RGB));
    
    newRGB->red_duty = 0;
    newRGB->green_duty = 0;
    newRGB->blue_duty = 0;
    
    newRGB->previous_red_duty = 0;
    newRGB->previous_green_duty = 0;
    newRGB->previous_blue_duty = 0;
    
    ledc_channel_config_t red_conf ={
        .channel = RED_CHANNEL,
        .hpoint = RED_HPOINT,
        .gpio_num = RED_PIN,
        .duty = 0,
        .flags.output_invert = 0,
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
        .timer_sel = 0
    };
    ledc_channel_config_t green_conf ={
        .channel = GREEN_CHANNEL,
        .hpoint = GREEN_HPOINT,
        .gpio_num = GREEN_PIN,
        .duty = 0,
        .flags.output_invert = 0,
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
        .timer_sel = 0
    };
    ledc_channel_config_t blue_conf ={
        .channel = BLUE_CHANNEL,
        .hpoint = BLUE_HPOINT,
        .gpio_num = Blue_PIN,
        .duty = 0,
        .flags.output_invert = 0,
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
        .timer_sel = 0
    };
    ledc_channel_config(&red_conf);
    ledc_channel_config(&green_conf);
    ledc_channel_config(&blue_conf);
    
    ledc_timer_config_t ledcTimerConfig = {
        .clk_cfg = LEDC_AUTO_CLK,
        .deconfigure = false,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 4000,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = 0
    };
    ledc_timer_config(&ledcTimerConfig);
    printf("init\n");
    return newRGB;
}

void setRGB(RGB_handle rgb, int red, int green, int blue){
    if (red >= MAX_DUTY){
        red = MAX_DUTY;
    }
    if (green >= MAX_DUTY){
        green = MAX_DUTY;
    }
    if (blue >= MAX_DUTY){
        blue = MAX_DUTY;
    }
    rgb->red_duty = red;
    printf("set red: %u previous %u\n", red, rgb->previous_red_duty);
    rgb->green_duty = green;
    printf("set green: %u previous %u\n", green, rgb->previous_green_duty);
    rgb->blue_duty = blue;
    printf("set blue: %u previous %u\n", blue, rgb->previous_blue_duty);

}

void updateRGB(RGB_handle rgb){
    if (rgb->previous_red_duty != rgb->red_duty)
    {
        printf("update red\n");
        rgb->previous_red_duty = rgb->red_duty;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, RED_CHANNEL, rgb->red_duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, RED_CHANNEL);
    }
    
    if (rgb->previous_green_duty != rgb->green_duty)
    {
        printf("update green\n");
        rgb->previous_green_duty = rgb->green_duty;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, GREEN_CHANNEL, rgb->green_duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, GREEN_CHANNEL);
    }
    
    if (rgb->previous_blue_duty != rgb->blue_duty)
    {
        printf("update blue\n");
        rgb->previous_blue_duty = rgb->blue_duty;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, BLUE_CHANNEL, rgb->blue_duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, BLUE_CHANNEL);
    }

    else if (rgb == NULL) {
        printf("LED handle is NULL!\n");
        return;
    }
    
}

