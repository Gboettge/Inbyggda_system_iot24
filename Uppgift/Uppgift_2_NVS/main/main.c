#include <stdio.h>
#include "Configuration_NVS.h"
#include "freertos/FreeRTOS.h"


myNvs_handle *nvs;
void app_main(void)
{
    nvs = nvs_init();
    ESP_LOGI("NVS main ", "number: %s", getSerialNumber(nvs));
    ESP_LOGI(TAG, "name: %s", getDeviceName(nvs));
    
    setSerialNumber(nvs, "5555");
    setDeviceName(nvs, "abcd");
    setSerialNumber(nvs, "000231");
    
    ESP_LOGI("NVS main ", "number: %s", getSerialNumber(nvs));
    ESP_LOGI(TAG, "name: %s", getDeviceName(nvs));

    setSerialNumber(nvs, "31a412xy911");
    setDeviceName(nvs, "Gustav2");
    setDeviceName(nvs, "Gustav2Gustav2Gustav2");

    ESP_LOGI("NVS main ", "number: %s", getSerialNumber(nvs));
    ESP_LOGI(TAG, "name: %s", getDeviceName(nvs));
    
    
    // nvsFree(nvs);
    // nvsErase();
}