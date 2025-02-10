#include <stdio.h>
#include "driver/i2c_master.h"
#include "driver/i2c_slave.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

// i2c_master_bus_config_t i2c_mst_config = {
//     .clk_source = I2C_CLK_SRC_DEFAULT,
//     .i2c_port = I2C_NUM_0,
//     .scl_io_num = GPIO_NUM_3,
//     .sda_io_num = GPIO_NUM_4,
//     .glitch_ignore_cnt = 7,
//     .flags.enable_internal_pullup = true,
// };

// i2c_master_bus_handle_t bus_handle;

// i2c_device_config_t dev_cfg = {
//     .dev_addr_length = I2C_ADDR_BIT_LEN_7,
//     .device_address = 0x58,
//     .scl_speed_hz = 100000,
// };

// i2c_master_dev_handle_t dev_handle;

i2c_slave_config_t i2c_slv_config = {
    .i2c_port = I2C_NUM_0,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .scl_io_num = GPIO_NUM_2,
    .sda_io_num = GPIO_NUM_3,
    .slave_addr = 0x58,
    .send_buf_depth = 100,
    .receive_buf_depth = 100,
};

i2c_slave_dev_handle_t slave_handle;
typedef enum {
    I2C_SLAVE_EVT_RX,
    I2C_SLAVE_EVT_TX
} i2c_slave_event_t;


void app_main(void)
{
    // ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
    // ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
        ESP_ERROR_CHECK(i2c_new_slave_device(&i2c_slv_config, &slave_handle));
    while (1)
    {
        printf("Hej\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}