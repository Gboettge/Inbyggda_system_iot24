#include <stdio.h>
#include "RGB_led_component.h"

color colors[] = {
    {255, 0, 0}, //red
    {0, 255, 0}, //green
    {0, 0, 255}, //blue
    {255, 150, 0}, //yellow
    {255, 0, 255}, //Magenta
    {0, 255, 255}, //cyan
    {255, 255, 255}, //white
    {75 ,0 ,130}, //purple
    {230, 29, 0},  //orange 9
    {0,0,0}, //OFF
    // {230, 59, 0},  //orange bäst hittils
    // {230, 89, 0}  //orange
    {255, 255, 0}, //yellow
    {255, 200, 0}, //yellow
    {255, 170, 0}, //yellow
    {255, 150, 0}, //yellow
    {255, 120, 0}, //yellow
    {255, 100, 0}, //yellow
    {255, 80, 0}, //yellow
    {255, 50, 0}, //yellow
    
};

const char *color_names[] = {
    "RED",
    "GREEN",
    "BLUE",
    "YELLOW",
    "MAGENTA",
    "CYAN",
    "WHITE",
    "PURPLE",
    "ORANGE",
    "NONE"
};

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

    if (red >= MAX_DUTY)
    {
        red = MAX_DUTY;
    }
    if (green >= MAX_DUTY)
    {
        green = MAX_DUTY;
    }
    if (blue >= MAX_DUTY)
    {
        blue = MAX_DUTY;
    }
    // int red_hpoint = 50;
    // int green_hpoint = 50;
    // int blue_hpoint = 50;
    // int tot = red + green + blue;

    // if(tot > 255){
    //     red_hpoint = (red *255)/tot; // lös float
    //     red_hpoint = ((red_hpoint * 2) +1 )/2;
    //     printf("%d\n", red_hpoint);
    //     green_hpoint = (green *255)/tot;//
    //     green_hpoint = ((green_hpoint * 2) +1 )/2;
    //     printf("%d\n", green_hpoint);
    //     blue_hpoint = (blue *255)/tot; //
    //     blue_hpoint = ((blue_hpoint * 2) +1 )/2;
    //     printf("%d\n", blue_hpoint);
    // }
    
    // rgb->red_duty = (uint8_t)red_hpoint;
    // printf("set red: %u previous %u\n", red, rgb->previous_red_duty);
    // rgb->green_duty = (uint8_t)green_hpoint;
    // printf("set green: %u previous %u\n", green, rgb->previous_green_duty);
    // rgb->blue_duty = (uint8_t)blue_hpoint;
    // printf("set blue: %u previous %u\n", blue, rgb->previous_blue_duty);

    rgb->red_duty = red;
    rgb->green_duty = green;
    rgb->blue_duty = blue;

    //weak
    // rgb->red_duty = red/5;
    // rgb->green_duty = green/5;
    // rgb->blue_duty = blue/5;


}

void updateRGB(RGB_handle rgb){

    if (rgb->previous_red_duty != rgb->red_duty)
    {
        // printf("update red\n");
        rgb->previous_red_duty = rgb->red_duty;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, RED_CHANNEL, rgb->red_duty);
        // ledc_set_duty_with_hpoint(LEDC_LOW_SPEED_MODE, RED_CHANNEL, rgb->red_duty*3, 0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, RED_CHANNEL);
    }
    
    if (rgb->previous_green_duty != rgb->green_duty)
    {
        // printf("update green\n");
        rgb->previous_green_duty = rgb->green_duty;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, GREEN_CHANNEL, rgb->green_duty);
        // ledc_set_duty_with_hpoint(LEDC_LOW_SPEED_MODE, GREEN_CHANNEL, rgb->green_duty*3, rgb->red_duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, GREEN_CHANNEL);
        
    }
    
    if (rgb->previous_blue_duty != rgb->blue_duty)
    {
        // printf("update blue\n");
        rgb->previous_blue_duty = rgb->blue_duty;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, BLUE_CHANNEL, rgb->blue_duty);//
        // ledc_set_duty_with_hpoint(LEDC_LOW_SPEED_MODE, BLUE_CHANNEL, rgb->blue_duty *3, rgb->red_duty + rgb->green_duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, BLUE_CHANNEL);
        // ledc_set_duty_and_update
    }

    else if (rgb == NULL) {
        printf("LED handle is NULL!\n");
        return;
    }

    
    
}

void fadeRGB(RGB_handle rgb){
    uint8_t redd = rgb->red_duty;
    uint8_t greend = rgb->green_duty;
    uint8_t blued = rgb->blue_duty;
    if (redd >= 11){
        redd = (redd/10) * 9;
        rgb->red_duty = redd;
    }
    else{
        rgb->red_duty = 0;
    }
    if (greend >= 11){
        greend = (greend/10) * 9;
        rgb->green_duty = greend;
    }
    else{
        rgb->green_duty = 0;
    }
    if (blued >= 11){
        blued = (blued/10) *9;
        rgb->blue_duty = blued;
    }
    else{
        rgb->blue_duty = 0;
    }
}

