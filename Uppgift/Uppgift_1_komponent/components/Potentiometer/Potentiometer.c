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
    newPot->channel = channel;
    newPot->unit_init_t.clk_src = 0;
    newPot->unit_init_t.ulp_mode = ADC_ULP_MODE_DISABLE;
    newPot->unit_init_t.unit_id = unit;
    adc_oneshot_new_unit(&newPot->unit_init_t, &newPot->adc1_handle_t);
    //adc_oneshot_del_unit(newPot->adc1_handle);
    return newPot;
}

void pot_update(pot_handle pot)
{
    printf("Hello\n");
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




/*
xxx init ( pin/adc, xxx )

xxx update (xxx)
uppdaterar = 

int getValue( xxx )

xxx setOnThreshold ( int threshold, bool risingEdge, xxx (*onThreshold)(int pin/adc, value, xxx), xxx )

*/

