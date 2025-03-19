#pragma once
#include "Button.h"
#include "Binary_Led.h"
#include "DISPLAY1.h"
#include "RGB_led_component.h"
#include "freertos/FreeRTOS.h"
#define COLOR_SIZE 9
#define PLAY_TIME 60
#define STARTUP_DURATION 8000

typedef enum{
    GUESS_COLOR_START,
    GUESS_COLOR_GAME,
    GUESS_COLOR_GAMEOVER,
    GUESS_COLOR_TIMES_UP,
    GUESS_COLOR_GENERATE_NEW
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
    TickType_t secondsTick;

    int lives;
    int correctPlacement;
    int score;
    int seconds;
    bool isGame;
    bool isWaiting;
    int choise;
} guess_color_t;

typedef guess_color_t * guess_color_handle;
void button_choise_one();
void button_choise_two();
void button_choise_three();
// (button_handle button, onbutton_f onPressed, void* arg)
// button_setOnPressed(button_choise_one);
// button_setOnPressed(button_choise_two);
// button_setOnPressed(button_choise_three);

guess_color_handle guess_color_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb);

void guess_color_start(guess_color_handle g1);

bool guess_color_play(guess_color_handle g1);

void guess_color_end(guess_color_handle g1);

void syncLives(guess_color_handle g1);

int getRandom(int value, int modulu);

int *get_x_randoms(int returnAmount, int modulu, int tickcount);