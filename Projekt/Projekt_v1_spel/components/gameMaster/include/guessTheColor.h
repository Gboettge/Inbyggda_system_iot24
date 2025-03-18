#pragma once
#include "Button.h"
#include "Binary_Led.h"
#include "DISPLAY1.h"
#include "RGB_led_component.h"
#include "freertos/FreeRTOS.h"


typedef enum{
    GUESS_COLOR_START,
    GUESS_COLOR_GAME,
    GUESS_COLOR_GAMEOVER,
    GUESS_COLOR_NONE
}guess_state;

typedef struct {
    button_handle btnOne;
    button_handle btnTwo;
    button_handle btnThree;
    b_led_handle bLedOne;
    b_led_handle bLedTwo;
    b_led_handle bLedThree;
    display_handle display;
    RGB_handle rgb;

    guess_state previousState;     
    guess_state currentState;
    guess_state nextState;     
    TickType_t previousTick;

    int lives;
    int correctPlacement;
    int score;
    int seconds;
    bool isGame;
} guess_color_t;

typedef guess_color_t * guess_color_handle;

guess_color_handle guess_color_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb);

void guess_color_start(guess_color_handle g1);

bool guess_color_play(guess_color_handle g1);

void guess_color_end(guess_color_handle g1);