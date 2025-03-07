#include <stdio.h>
#include "RGB_led_component.h"
RGB_handle rgb;

void app_main(void)
{
rgb = rgb_init();
setRGB(rgb, 255, 255, 255);
    while(1){
        updateRGB(rgb);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

}