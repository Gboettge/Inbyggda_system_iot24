#pragma once
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"


typedef struct {
    adc_unit_t adc_unit;
    adc_channel_t channel;
    int value;
    int threshold;
    bool risingEdge;
    adc_oneshot_unit_init_cfg_t init_config;
    adc_oneshot_unit_handle_t adc_handle;
} pot_t;

typedef pot_t* pot_handle;

pot_handle potentiometer_init(adc_unit_t unit, adc_channel_t channel);

void pot_update(pot_handle pot);

int pot_get_value(pot_handle pot);
