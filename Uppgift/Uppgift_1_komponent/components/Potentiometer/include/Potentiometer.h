#pragma once
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"
#include "hal/adc_types.h"


typedef struct {
    //adc_unit_t adc_unit;
    adc_oneshot_unit_handle_t adc1_handle_t;
    adc_oneshot_unit_init_cfg_t unit_init_t;
    adc_oneshot_chan_cfg_t chan_conf_t;  //fortsätt här
    int value;
    int threshold;
    bool risingEdge;
    void (*onThreshold)(int pin, int value);
    

} pot_t;

typedef pot_t* pot_handle;

pot_handle potentiometer_init(adc_unit_t unit, adc_channel_t channel);

void pot_update(pot_handle pot);

int pot_get_value(pot_handle pot);
