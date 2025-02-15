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
    newPot->adc_unit = unit;
    newPot->channel = channel;
    newPot->value = 0;
    newPot->threshold = 0;
    newPot->risingEdge = false;
    //newPot->onThreshold = NULL;
    newPot->init_config.unit_id = unit;
    //newPot->adc_handle =
    printf("Pot init success, channel: %d\n", channel);
    esp_err_t adc_oneshot_new_unit(const adc_oneshot_unit_init_cfg_t *init_config, adc_oneshot_unit_handle_t *ret_unit);
    return newPot;
}

void pot_update(pot_handle pot)
{
    // pot->channel_config, &(pot->adc_raw
    if (pot != NULL)
    {
        
        pot->value = adc_oneshot_read(pot->adc_handle, pot->channel, &(pot->value));
        printf("%d", pot->value);
    }
    
}

int pot_get_value(pot_handle pot)
    {
        if (pot == NULL)
            return 0;
        return pot->value;
    }



/*
xxx init ( pin/adc, xxx )

xxx update (xxx)
uppdaterar = 

int getValue( xxx )

xxx setOnThreshold ( int threshold, bool risingEdge, xxx (*onThreshold)(int pin/adc, value, xxx), xxx )

*/

