#include <stdio.h>
#include "RGB_led_component.h"
#include "button.h"
#include "DISPLAY1.h"
#include "driver/adc.h"

RGB_handle rgb;
button_handle redBtn;
display_s *display;

// lös så value 3 inte kan bli samma som value 1

int getRandom(int value, int modulu, int i)
{
    int newval = value % modulu;
    if (newval == i)
    {
        newval = (value + 1) % modulu;
    }
    return newval;
}
// läs värde från en pin, använd modulu(antalet alternativ) för att slumpa (0-4095)
void app_main(void)
{

    redBtn = button_init(2, GPIO_PULLUP);
    display = display_init();
    // greenBtn = button_init(3, GPIO_PULLUP);
    // blueBtn = button_init(4, GPIO_PULLUP);
    rgb = rgb_init();
    setRGB(rgb, 55, 55, 55);

    int i = -1;
    TickType_t previousSwitch = 0;
    while (1)
    {
        TickType_t currentTick = xTaskGetTickCount();
        // fadeRGB(rgb); //disco
        updateRGB(rgb);
        button_update(redBtn);

        vTaskDelay(pdMS_TO_TICKS(40));
        if (button_isPressed(redBtn))
        {
            if (currentTick - previousSwitch >= pdMS_TO_TICKS(500))
            {
                int adc_reading = (int)previousSwitch;
                ESP_LOGI(TAG, "ADC Reading: %d", adc_reading);
                i++;
                int myrandom = getRandom(adc_reading, 10, i);
                if (i == 10)
                {
                    i = 0;
                }
                char randomstr[12];
                char myInt[12];
                snprintf(randomstr, sizeof(randomstr), "%d", myrandom);
                snprintf(myInt, sizeof(myInt), "%d", i);
                previousSwitch = currentTick;
                setRGB(rgb, colors[i].red, colors[i].green, colors[i].blue);
                display_ui(display, color_names[i], color_names[myrandom], color_names[(myrandom + 5) % 10], randomstr, myInt);
                // ESP_LOGI(TAG, "%s", color_names[i]);
            }
        }
        // vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
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