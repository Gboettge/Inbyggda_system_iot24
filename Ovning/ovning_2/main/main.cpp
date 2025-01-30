#include <stdio.h>
#include "Helper_Component.h"
#include "printer.h"
#include "esp_log.h"

extern "C"
{
    void app_main(void)
    {
        int a = ovning_2::func();
        ESP_LOGI("Main", " gor value %d", a);
        a = inbyggda_iot24::func();
        ESP_LOGI("Main", " gor value %d", a);

        ovning_2::printNumbers(1, 10);
        ovning_2::takeTimeAndPrintEverySecond(-10);
       // ovning_2::multiply(7, 8);
       
        PRINTF_COLOR(ANSI_MAGENTA, "%d" NEW_LINE, ovning_2::multiply(7,8));
    }
}