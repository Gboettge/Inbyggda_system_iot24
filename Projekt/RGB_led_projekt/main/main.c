#include <stdio.h>
#include "RGB_led_component.h"
#include "button.h"
RGB_handle rgb;
button_handle redBtn;

void app_main(void)
{
    redBtn = button_init(2, GPIO_PULLUP); 
    // greenBtn = button_init(3, GPIO_PULLUP); 
    // blueBtn = button_init(4, GPIO_PULLUP); 
    rgb = rgb_init();
    setRGB(rgb, 255, 255, 0);
    int i = 0;
    TickType_t previousSwitch = 0;
    while (1)
    {
        TickType_t currentTick = xTaskGetTickCount();
        updateRGB(rgb);
        button_update(redBtn);
        if (i == RED && button_isPressed(redBtn) == true){
            ESP_LOGI(TAG, "Correct! pause: 5s"); 
            setRGB(rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
            updateRGB(rgb);
            vTaskDelay(pdMS_TO_TICKS(5000));
            previousSwitch = currentTick;
            
        }
        if (currentTick - previousSwitch >= pdMS_TO_TICKS(1000))
        {   
            i++;
            if (i == 9){
                i = 0;
            }
            previousSwitch = currentTick;
            setRGB(rgb, colors[i].red, colors[i].green, colors[i].blue);
            
            ESP_LOGI(TAG, "%s", color_names[i]);
            
        }
        vTaskDelay(pdMS_TO_TICKS(20));
                // vTaskDelay(pdMS_TO_TICKS(1000));
    }
}