#pragma once
#include <stdio.h>
#include "freertos/FreeRTOS.h"

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
#define PRINTF_COLOR(color, format_string, ...) \
    printf("%s" format_string "%s", color, ##__VA_ARGS__, ANSI_RESET);


namespace ovning_2
{
    int func(void);
    void printNumbers(int start, int stop);
    void takeTimeAndPrintEverySecond(int time);
    int multiply(int a, int b);
}
