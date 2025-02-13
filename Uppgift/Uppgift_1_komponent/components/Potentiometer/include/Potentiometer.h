#pragma once
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"

typedef struct{
    int pin;
    int level;
    

} pot_t;

typedef pot_t* pot_handle;