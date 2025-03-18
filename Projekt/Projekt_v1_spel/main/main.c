#include <stdio.h>
#include "Button.h"
#include "Binary_Led.h"
#include "DISPLAY1.h"
#include "RGB_led_component.h"
#include "gameMaster.h"

    button_handle btnOne;
    button_handle btnTwo;
    button_handle btnThree;
    display_handle display;
    RGB_handle rgb;
    b_led_handle bLedOne;
    b_led_handle bLedTwo;
    b_led_handle bLedThree;
    gm_handle gameMaster;
    guess_color_handle gameOne;
    

    
void app_main(void)
{
    printf("Initializing components...\n");
    bLedOne = b_led_init(17, BL_LIGHT_ON, false);
    bLedTwo = b_led_init(16, BL_LIGHT_ON, false);
    bLedThree = b_led_init(9, BL_LIGHT_ON, false);
    btnOne = button_init(2, GPIO_PULLUP);
    btnTwo = button_init(3, GPIO_PULLUP);
    btnThree = button_init(4, GPIO_PULLUP);
    display = display_init();
    rgb = rgb_init();
    gameOne = guess_color_init(btnOne, btnTwo, btnThree, bLedOne, bLedTwo, bLedThree, display, rgb);
    gameMaster = gm_init(btnOne, btnTwo, btnThree, bLedOne, bLedTwo, bLedThree, display, rgb, gameOne);
    
    printf("Components initialized.\n");


   
   while(1){
        button_update(btnOne);
        button_update(btnTwo);
        button_update(btnThree);
        b_led_update(bLedOne);
        b_led_update(bLedTwo);
        b_led_update(bLedThree);
        updateRGB(rgb);
        gm_update(gameMaster);
        vTaskDelay(pdMS_TO_TICKS(30));
        // setRGB(rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
    }
}