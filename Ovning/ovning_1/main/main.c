#include <stdio.h>
#include "esp_log.h"

const static char * TAG = "MAIN";

#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_MAGENTA "\033[0;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RESET "\033[0m"

void app_main(void)
{
    ESP_LOGI(TAG, "Hello World for my %d time", 1);
    
    const char * test_string = "test";

    printf("%s%s%s", ANSI_CYAN, test_string, ANSI_RESET "\n");
}