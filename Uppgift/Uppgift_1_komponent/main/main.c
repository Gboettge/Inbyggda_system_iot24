#include <stdio.h>
#include "Button.h"


button_handle btn1;
button_handle btn2;
button_handle btn3;

void app_main(void)
{
    printf("Starting main\n");
   
    btn1 = button_init(GPIO_NUM_15, GPIO_PULLUP);
    btn2 = button_init(GPIO_NUM_5, GPIO_PULLDOWN);
    btn3 = button_init(GPIO_NUM_20, GPIO_PULLUP);
    
    button_setOnPressed(btn1, button_print_press_num);
    button_setOnPressed(btn2, button_print_num_x_ten);
    
     while(1)
     {
         //printf("%d\n", isPressed(btn1));
         vTaskDelay(pdMS_TO_TICKS(20));
         button_update(btn1);
         button_update(btn2);
         button_update(btn3);
     }
}