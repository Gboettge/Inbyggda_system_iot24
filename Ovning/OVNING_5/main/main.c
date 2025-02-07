#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

#define RXD_PIN (GPIO_NUM_4)
#define TXD_PIN (GPIO_NUM_5)
#define UART_BUFFER_SIZE 1024

const uart_port_t uart_num = UART_NUM_1;
const uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT,
};

// Setup UART buffered IO with event queue
//const int uart_buffer_size = (1024 * 2);
uint8_t uart_buffer[UART_BUFFER_SIZE] = {0};

QueueHandle_t uart_queue;

//uint8_t data[128];

void app_main(void)
{
    
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, UART_BUFFER_SIZE, UART_BUFFER_SIZE, 10, &uart_queue, 0));

    xQueueCreate(UART_BUFFER_SIZE, 10);

    // Write data to UART.
    char* test_str = "UNO REVERSE.\n";
    int length = 0;
    int counter = 0;
    while (1)
    {

        // ESP_ERROR_CHECK()
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t *)&length));
        length = uart_read_bytes(uart_num, uart_buffer, UART_BUFFER_SIZE, 100);
        printf("%d\n", length);
        printf("%s\n", uart_buffer);
        vTaskDelay(pdMS_TO_TICKS(200));
        counter++;
        if (counter == 5)
        {
            int UNO = uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
            printf("Sent:%d\n", UNO);
            counter = 0;
        }
        // för read
    }
}