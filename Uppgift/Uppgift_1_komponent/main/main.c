#include <stdio.h>
#include "Button.h"

//Skapa detete för button
//
button_handle btn1;
void app_main(void)
{
    btn1 = button_init(GPIO_NUM_15, GPIO_PULLDOWN);
    printf("Pin:%d Mode%d\n", btn1->pin, btn1->mode);
    //TickType_t startTick = xTaskGetTickCount();
    
     while(1)
     {
         //printf("%d\n", isPressed(btn1));
         vTaskDelay(pdMS_TO_TICKS(3));
         update(btn1);
     }
}