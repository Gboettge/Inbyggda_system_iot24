#include <stdio.h>
#include "Configuration_NVS.h"
#include "freertos/FreeRTOS.h"


myNvs_handle *nvs;
void app_main(void)
{
    nvs = nvs_init();
    setSerialNumber(nvs, "31a412xy9");
    setDeviceName(nvs, "Gustav");
    char * serialNumber = getSerialNumber(nvs);
    char * deviceName = getDeviceName(nvs);
   
    
    
    
    
    ESP_LOGI("NVS main ", "number: %s", serialNumber);
    ESP_LOGI(TAG, "name: %s", deviceName);
    
    nvsClose(nvs);
    //nvsDestroy();
}