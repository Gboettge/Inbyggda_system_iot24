#include <stdio.h>
#include "esp_log.h"

const static char * TAG = "MAIN";

#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_MAGENTA "\033[0;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_HCYAN "\e[0;96m" //high intensity cyan
#define ANSI_BHCYAN "\e[1;96m" //BOLD high intensity cyan
#define ANSI_RESET "\033[0m"
#define NEW_LINE "\n"
#define NEW_WORLD_COUNT 1

#define PRINTF_COLOR(color, format_string, ...) \
    printf("%s" format_string "%s", color, ##__VA_ARGS__, ANSI_RESET);

#define PRINTF_GROUP_1(format, ...)\
    PRINTF_COLOR(ANSI_BLUE, "Group 1 ");\
    PRINTF_COLOR(ANSI_RESET, format, ##__VA_ARGS__);

#define PRINTF_COLOR_WITH_LINE(color, format_string, ...)\
    PRINTF_COLOR(ANSI_MAGENTA, "[%s:%d]", __FILE__, __LINE__);\
    PRINTF_COLOR(color, format_string, ##__VA_ARGS__);


#define PRINT_GUSTAV(color, format_string, ...)\
    PRINTF_COLOR(color, format_string, ##__VA_ARGS__)





void app_main(void)
{
    ESP_LOGI(TAG, "Hello World for my %d time", NEW_WORLD_COUNT);
    
    const char * test_string =  "t"
                                "e"
                                "s"
                                "t";

    PRINTF_COLOR(ANSI_RED, "%s"NEW_LINE, test_string);

    PRINT_GUSTAV(ANSI_YELLOW, "Gustav %s", NEW_LINE);
    
    PRINT_GUSTAV(ANSI_MAGENTA, "Anton %skan inte %s%s%s", ANSI_BHCYAN, ANSI_GREEN, "sova.", NEW_LINE);

    PRINTF_GROUP_1("Hello World %d" NEW_LINE, NEW_WORLD_COUNT);

    PRINTF_COLOR_WITH_LINE(ANSI_YELLOW, "Hello world %d" NEW_LINE, NEW_WORLD_COUNT);
}