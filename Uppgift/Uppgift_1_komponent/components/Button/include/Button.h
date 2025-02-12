#pragma once
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

typedef enum {
    GPIO_PULLUP,
    GPIO_PULLDOWN 
}strapping_mode;

typedef struct {
    int pin;
    strapping_mode mode;
    int latch;
    bool pressed;
    void (*onpressed)(int pin);
} button;

typedef button* button_handle;

button_handle button_init(int pin, strapping_mode pull);

void button_update(button_handle button);

bool button_isPressed (button_handle button);

void button_setOnPressed (button_handle button, void(*onPressed)(int pin));

void button_print_press_num (int pin);

void button_print_num_x_ten(int pin);