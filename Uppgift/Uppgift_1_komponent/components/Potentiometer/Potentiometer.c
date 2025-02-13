#include <stdio.h>
#include "Potentiometer.h"


pot_handle potentiometer_init(GPIO_ADC pin, ADC_LIMIT limit){
    pot_handle newPot = pvPortMalloc(sizeof(pot_t));
    newPot->adc_raw = 0;
    newPot->channel_config = channel;
    newPot->limit = limit;
    newPot->pin = pin;
    newPot->config.atten = limit;
    newPot->config.bitwidth = ADC_BITWIDTH_DEFAULT;
}


xxx init ( pin/adc, xxx )

xxx update (xxx)
uppdaterar = 

int getValue( xxx )

xxx setOnThreshold ( int threshold, bool risingEdge, xxx (*onThreshold)(int pin/adc, value, xxx), xxx )

