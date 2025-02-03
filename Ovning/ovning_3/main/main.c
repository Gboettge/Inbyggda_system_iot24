#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h"

#define BUTN_1_PIN GPIO_NUM_2
#define BUTN_2_PIN GPIO_NUM_3
//#define BUTN_1_OUT GPIO_NUM_5
// #define BUTN_2_OUT GPIO_NUM_5
//nedanstående tagit från https://github.com/espressif/esp-idf/blob/v5.4/examples/peripherals/ledc/ledc_basic/main/ledc_basic_example_main.c
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (4000) // Frequency in Hertz. Set frequency at 4 kHz

static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void app_main(void)
{
example_ledc_init();
ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
gpio_set_direction(BUTN_1_PIN, GPIO_MODE_INPUT);
gpio_set_direction(BUTN_2_PIN, GPIO_MODE_INPUT);

//gpio_set_direction(BUTN_1_OUT, GPIO_MODE_OUTPUT);
// int green = gpio_set_level(BUTN_1_PIN, 1);
// int red = gpio_set_level(BUTN_2_PIN, 1);
int green = gpio_get_level(BUTN_1_PIN);
int red = gpio_get_level(BUTN_2_PIN);
TickType_t startTick = xTaskGetTickCount();
int upLatch = 0;
int downLatch = 0;


int PWM = LEDC_DUTY;
    while (1){
        vTaskDelay(pdMS_TO_TICKS(60));
        green = gpio_get_level(BUTN_1_PIN);
        red = gpio_get_level(BUTN_2_PIN);

        if((green == 1 && upLatch == 0 && PWM !=8096))
        {
            TickType_t tickDiff = xTaskGetTickCount() - startTick;
            if (tickDiff >= pdMS_TO_TICKS(60))
            {
                startTick = xTaskGetTickCount();
                upLatch = 1;
                PWM += 1012;
                if (PWM > 8096)
                    PWM = 8096;
                printf("Green PWM:%d\n", PWM);
                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, PWM);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            }
        }
        else if (green == 0 && upLatch == 1)
        {
            TickType_t tickDiff = xTaskGetTickCount() - startTick;
            if (tickDiff >= pdMS_TO_TICKS(60))
            {
                startTick = xTaskGetTickCount();
                upLatch = 0;
            }
        }

        if((red == 1 && downLatch == 0 && PWM != 0))
        {
            TickType_t tickDiff = xTaskGetTickCount() - startTick;
            if (tickDiff >= pdMS_TO_TICKS(60))
            {
                startTick = xTaskGetTickCount();
                downLatch = 1;
                PWM -= 1012;
                if (PWM < 0)
                    PWM = 0;
                printf("Red PWM:%d\n", PWM);
                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, PWM);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
                //ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL, PWM);
            }
        }
        else if (red == 0 && downLatch == 1)
        {
            TickType_t tickDiff = xTaskGetTickCount() - startTick;
            if (tickDiff >= pdMS_TO_TICKS(60))
            {
                startTick = xTaskGetTickCount();
                downLatch = 0;
            }
        }

        
    }
}