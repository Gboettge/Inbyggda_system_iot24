#pragma once
#include "Button.h"
#include "Binary_Led.h"
#include "DISPLAY1.h"
#include "RGB_led_component.h"
#include "freertos/FreeRTOS.h"
#include "guessTheColor.h"
#include "esp_err.h"
#include "esp_log.h"
#define MAX_COLORS 9

typedef enum{
    GM_MENU,
    GM_GAME,
    GM_HIGHSCORE,
    GM_CYCLE_COLORS,
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
    guess_color_handle guess_color;

    gm_state previousState;     
    gm_state currentState;
    gm_state nextState;     
    TickType_t previousTick;
    TickType_t secondsTick;
    bool gameRunning;
    int score;
    int seconds;
    int choise;
    bool firstTime;
    int colorCycle;
} gm;

typedef gm* gm_handle;

void gm_choise_one();
void gm_choise_two();
void gm_choise_three();

gm_handle gm_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb, guess_color_handle guess_color);

void gm_update(gm_handle gm);

void gm_init_games(gm_handle gm); //init för guess_color

void gm_free_games(gm_handle gm); //frigör guess_color

void gm_get_guess_highscore(gm_handle gm); //hämtar score från guess_color (spelet)


