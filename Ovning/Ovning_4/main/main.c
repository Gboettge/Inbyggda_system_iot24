#include "sdkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_task_wdt.h"
#include "driver/gpio.h"
#define BTN_PRESS GPIO_NUM_5


#define TWDT_TIMEOUT_MS         3000
#define TASK_RESET_PERIOD_MS    2000
#define MAIN_DELAY_MS           10000
#define IDLE_CORE_0_BIT         0b01
#define IDLE_core_1_BIT         0b10
void knappFan()
{  
    //int knapp = BTN_PRESS;
    int number = 0;
    while(1)
    {
        int knapp = gpio_get_level(BTN_PRESS);
        vTaskDelay(pdMS_TO_TICKS(200));
        number++;
        printf("%d\n", number);
        if(knapp == 1)
        {
            ESP_ERROR_CHECK(esp_task_wdt_reset());
            return;
        }
    }
}

void app_main(void)
{
    esp_task_wdt_config_t twdt_config = {
        .timeout_ms = TWDT_TIMEOUT_MS,
        //.idle_core_mask = (1 << CONFIG_FREERTOS_NUMBER_OF_CORES) - 1, // Bitmask of all cores
        .idle_core_mask = IDLE_CORE_0_BIT | IDLE_core_1_BIT, // Bitmask of all cores
        
        .trigger_panic = false,
    };
    
    ESP_ERROR_CHECK(esp_task_wdt_reconfigure(&twdt_config));
    printf("TWDT initialized\n");
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    gpio_set_direction(BTN_PRESS, GPIO_MODE_INPUT);
    
    while(1)
    {
        //gpio_get_level(BTN_PRESS);
        // printf("%d", gpio_get_level(BTN_PRESS));
        // printf("TWDT initialized\n");
        // vTaskDelay(pdMS_TO_TICKS(200));
        knappFan();
    }


    //esp_err_t esp_task_wdt_init(const esp_task_wdt_config_t *config);


    // gpio_set_direction(BTN_PRESS, GPIO_MODE_INPUT);
    // TickType_t startTick = xTaskGetTickCount();
    // int upLatch = 0;
    // int downLatch = 0;
    // int PWM = 0;

    // while (1)
    // {
    //     vTaskDelay(pdMS_TO_TICKS(60));
    //     int green = gpio_get_level(BTN_PRESS);
 

    //     if((green == 1 && upLatch == 0 && PWM !=8096))
    //     {
    //         TickType_t tickDiff = xTaskGetTickCount() - startTick;
    //         if (tickDiff >= pdMS_TO_TICKS(60))
    //         {
    //             startTick = xTaskGetTickCount();
    //             upLatch = 1;
    //             PWM += 12;
    //             if (PWM > 8096)
    //                 PWM = 8096;
    //             printf("Green PWM:%d\n", PWM);
               
    //         }
    //     }
    //     else if (green == 0 && upLatch == 1)
    //     {
    //         TickType_t tickDiff = xTaskGetTickCount() - startTick;
    //         if (tickDiff >= pdMS_TO_TICKS(60))
    //         {
    //             startTick = xTaskGetTickCount();
    //             upLatch = 0;
    //         }
    //     }       
    // }
}