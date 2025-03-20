#pragma once
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ssd1306.h"
#include <string.h>


#ifdef TAG
#undef TAG
#endif
#define TAG "Display"

#define I2C_BUS_PORT  0

#define EXAMPLE_LCD_PIXEL_CLOCK_HZ    (400 * 1000)
#define EXAMPLE_PIN_NUM_SDA           6
#define EXAMPLE_PIN_NUM_SCL           7
#define EXAMPLE_PIN_NUM_RST           -1
#define EXAMPLE_I2C_HW_ADDR           0x3C

#define EXAMPLE_LCD_H_RES              128
#define EXAMPLE_LCD_V_RES              64

// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8


typedef struct{
    lv_disp_t *disp;
    lv_obj_t *leftTop;
    lv_obj_t *leftCenter;
    lv_obj_t *leftBottom;
    lv_obj_t *rightTop;
    lv_obj_t *rightCenter;
    lv_obj_t *rightBottom;
   
}display_s;

typedef  display_s * display_handle;

display_s *display_init();

// void display_ui(display_s *disp);
void display_ui(display_s *display, char* newleftTop, char* newleftMid, char* newleftButtom, char* newRightTop, char* newRightCenter, char* newRightBottom);
//leftTop, leftMid, leftButtom, rightTop, rightBottom

void display_update(display_s *display, char* answear);
void display_update_time(display_s *display, char* time);

void display_update_fullscreen(display_s *display, char* newleftTop, char* newleftMid, char* newleftButtom, char* newRightTop, char* newRightCenter, char* newRightBottom);

void display_clear(display_s *display);