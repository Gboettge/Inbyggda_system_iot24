#pragma once
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

typedef struct BUTTON{
    int pin;


} BUTTON;

void init_button(pin, x);

void update(xxx);

bool isPressed (xxx);

void setOnPressed ( void(*onPressed)(int pin));

