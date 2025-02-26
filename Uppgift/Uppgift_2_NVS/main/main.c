#include <stdio.h>
#include "Configuration_NVS.h"


myNvs_handle nvs;
void app_main(void)
{
    myNvs_handle *nsd = nvs_init();
    //getDeviceName(&nvs);
    setDeviceName(nsd, "Gustav");
    //getDeviceName(&nvs);
    char* deviceName = getDeviceName(nsd);
    
    
    ESP_LOGI(TAG, "%s", deviceName);
    nvsDestroy(nsd);
}