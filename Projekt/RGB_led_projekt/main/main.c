#include <stdio.h>
#include "RGB_led_component.h"
RGB_handle rgb;

void app_main(void)
{
    rgb = rgb_init();
    setRGB(rgb, 255, 255, 0);
    while (1)
    {
        updateRGB(rgb);
        vTaskDelay(pdMS_TO_TICKS(20));

        for (int i = 0; i <= 8; i++)
        {
            setRGB(rgb, colors[i].red, colors[i].green, colors[i].blue);
            updateRGB(rgb);
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }
}