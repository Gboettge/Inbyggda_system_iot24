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
} button;

typedef button* button_handle;

button_handle button_init(int pin, strapping_mode pull);

void update(button_handle button);

bool isPressed (button_handle button);