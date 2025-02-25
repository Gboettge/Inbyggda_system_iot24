#include <stdio.h>
#include "Configuration_NVS.h"


myNvs_handle nvs;
void app_main(void)
{
    nvs_init();
    getDeviceName(nvs);
    setDeviceName("Gustav");
    getDeviceName(nvs);
}