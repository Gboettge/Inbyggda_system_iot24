#pragma once
#include "Button.h"
#include "Binary_Led.h"
#include "DISPLAY1.h"
#include "RGB_led_component.h"
#include "freertos/FreeRTOS.h"


typedef enum{
    GM_START,
    GM_GAME,
    GM_GAMEOVER,
    GM_NONE
}gm_state;

typedef struct {
    button_handle btnOne;
    button_handle btnTwo;
    button_handle btnThree;
    display_handle display;
    RGB_handle rgb;
    b_led_handle bLedOne;
    b_led_handle bLedTwo;
    b_led_handle bLedThree;
    gm_state previousState;     
    gm_state currentState;
    gm_state nextState;     
    TickType_t previousTick;
} gm;

typedef gm* gm_handle;

gm_handle gm_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb);

void gm_update(gm_handle gm);


