#include <stdio.h>
#include "RGB_led_component.h"
#include "button.h"
#include "DISPLAY1.h"
#include "driver/adc.h"


RGB_handle rgb;
button_handle redBtn;
display_s *display;
int getRandom(int value, int modulu)
{
    return value % modulu;
}
//läs värde från en pin, använd modulu(antalet alternativ) för att slumpa (0-4095)
void app_main(void)
{
    redBtn = button_init(2, GPIO_PULLUP); 
    display = display_init();
    // greenBtn = button_init(3, GPIO_PULLUP); 
    // blueBtn = button_init(4, GPIO_PULLUP); 
    rgb = rgb_init();
    setRGB(rgb, 55, 55, 55);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);

    int i = -1;
    TickType_t previousSwitch = 0;
    while (1)
    {
        TickType_t currentTick = xTaskGetTickCount();
        // fadeRGB(rgb); //disco
        updateRGB(rgb);
        button_update(redBtn);
        // if (i == RED && button_isPressed(redBtn) == true){
        //     ESP_LOGI(TAG, "Correct! pause: 5s");
        //     setRGB(rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
        //     updateRGB(rgb);
        //     vTaskDelay(pdMS_TO_TICKS(5000));
        //     button_update(redBtn);
        //     previousSwitch = currentTick;

        // }
        // if (currentTick - previousSwitch >= pdMS_TO_TICKS(2000))
        // {
        //     i++;
        //     if (i == 9){
        //         i = 0;
        //     }
        //     previousSwitch = currentTick;
        //     setRGB(rgb, colors[i].red, colors[i].green, colors[i].blue);

        //     ESP_LOGI(TAG, "%s", color_names[i]);
        // }
        if (button_isPressed(redBtn))
        {
            if (currentTick - previousSwitch >= pdMS_TO_TICKS(500))
            {
                int adc_reading = adc1_get_raw(ADC1_CHANNEL_0);
                int myrandom = getRandom(adc_reading, 10);
                i++;
                if (i == 10)
                {
                    i = 0;
                }
                char randomstr[4];
                sprintf(randomstr, "%d", myrandom);
                char myInt[4];
                sprintf(myInt, "%d", i);
                previousSwitch = currentTick;
                setRGB(rgb, colors[i].red, colors[i].green, colors[i].blue);
                display_ui(display, color_names[i], NULL, NULL, randomstr, myInt);
                ESP_LOGI(TAG, "%s", color_names[i]);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(40));
                // vTaskDelay(pdMS_TO_TICKS(1000));
    }
}