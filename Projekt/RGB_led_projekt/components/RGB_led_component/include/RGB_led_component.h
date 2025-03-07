#pragma once
#include "driver/ledc.h" 
#include "freertos/FreeRTOS.h"
#define MAX_DUTY 255

#define RED_PIN 2
#define GREEN_PIN 3
#define Blue_PIN 4
//#define LEDC_TIMER_8_BIT // 8-bitar (0-255)

#define RED_HPOINT 0
#define GREEN_HPOINT 0
#define BLUE_HPOINT 0

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

typedef struct
{
    uint8_t red_duty;
    uint8_t green_duty;
    uint8_t blue_duty;
    uint8_t previous_red_duty;
    uint8_t previous_green_duty;
    uint8_t previous_blue_duty;
    // color_index redChannel;
    // color_index greenChannel;
    // color_index blueChannel;
    
}color;

typedef color * RGB_handle;

// color colors[] = {
// {255, 0, 0}, //red
// {0, 255, 0}, //green
// {0, 0, 255}, //blue
// {255, 255, 0}, //yellow
// {255, 0, 255}, //Magenta
// {0, 255, 255}, //cyan
// {255, 255, 255} //white
// };

typedef enum{
RED = 0,
GREEN,
BLUE,
Yellow,
MAGENTA,
CYAN,
WHITE
}color_index;

RGB_handle rgb_init();

void setRGB(RGB_handle rgb, int red, int green, int blue);

void updateRGB(RGB_handle rgb);