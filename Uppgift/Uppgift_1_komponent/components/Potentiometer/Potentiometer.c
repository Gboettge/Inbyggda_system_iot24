#include <stdio.h>
#include "Potentiometer.h"

#define TAG "POT"
/*
, adc_channel_t channel*/
pot_handle potentiometer_init(adc_unit_t unit, adc_channel_t channel){
    pot_handle newPot = pvPortMalloc(sizeof(pot_t));

    if (newPot == NULL) {
        ESP_LOGE(TAG, "Memory allocation failed");
        return NULL;
    }
    newPot->value = 0;
    newPot->onThreshold = NULL; //
    newPot->risingEdge = true;
    //newPot->threshold = threshold; //
    newPot->channel = channel;
    newPot->unit_init_t.clk_src = 0;
    newPot->unit_init_t.ulp_mode = ADC_ULP_MODE_DISABLE;
    newPot->unit_init_t.unit_id = unit;
    newPot->onThreshold = NULL;
    newPot->thresholdReached = 0;
    adc_oneshot_new_unit(&newPot->unit_init_t, &newPot->adc1_handle_t);
    //adc_oneshot_del_unit(newPot->adc1_handle);
    return newPot;
}

void pot_update(pot_handle pot)
{
    TickType_t current_tick = xTaskGetTickCount();
    if(pot->onThreshold != NULL)
    {
        if(pot->value > pot->threshold && pot->risingEdge == true)
        {
            pot->onThreshold(pot->channel, pot->value);
            pot->risingEdge = false;
            pot->thresholdReached = current_tick;
        }
        if(pot->value < pot->threshold)
        {
            if (current_tick - pot->thresholdReached >= pdMS_TO_TICKS(2000))
            pot->risingEdge = true;
        }
    }
    
    
    //esp_err_t err = adc_oneshot_read(pot->adc1_handle_t, pot->unit_init_t.unit_id, &(pot->value));
    esp_err_t err = adc_oneshot_read(pot->adc1_handle_t, pot->channel, &(pot->value));
    if (err == ESP_OK) {
        printf("ADC Value: %d\n", pot->value);
    } else {
        printf("ADC read error: %d\n", err);
    }
}

int pot_get_value(pot_handle pot)
{
    if (pot == NULL)
        return 0;
    return pot->value;
}

void pot_setOnThreshold(pot_handle pot, int threshold, void(*onThreshold)(adc_channel_t channel, int value)) 
{
    pot->threshold = threshold;
    pot->onThreshold = onThreshold;
}

void pot_printThresholdReach(adc_channel_t channel, int value){
    printf("Threshold reached! Channel: %d, Value: %d\n", channel, value);
}

/*
xxx init ( pin/adc, xxx )

xxx update (xxx)
uppdaterar = 

int getValue( xxx )

xxx setOnThreshold ( int threshold, bool risingEdge, xxx (*onThreshold)(int pin/adc, value, xxx), xxx )

*/

