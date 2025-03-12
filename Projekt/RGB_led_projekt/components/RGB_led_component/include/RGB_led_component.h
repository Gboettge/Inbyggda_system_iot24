#pragma once
#include "driver/ledc.h" 
#include "freertos/FreeRTOS.h"
#include "esp_log.h"

#define TAG "RGB"
#define MAX_DUTY 255

#define RED_PIN 23
#define GREEN_PIN 22
#define Blue_PIN 20
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
    
}RGB;

typedef RGB * RGB_handle;

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}color;

extern color colors[];

extern const char *color_names[];

typedef enum{
RED = 0,
GREEN,
BLUE,
Yellow,
MAGENTA,
CYAN,
WHITE,
PURPLE,
ORANGE,
OFF
}color_index;

RGB_handle rgb_init();

void setRGB(RGB_handle rgb, int red, int green, int blue);

void updateRGB(RGB_handle rgb);

void fadeRGB(RGB_handle rgb);