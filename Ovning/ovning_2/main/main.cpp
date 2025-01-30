#include <stdio.h>
#include "Helper_Component.h"
#include "printer.h"
#include "esp_log.h"

extern "C"
{
void app_main(void)
{
    int a = func();
    ESP_LOGI("Main", " gor value %d", a);
}
}