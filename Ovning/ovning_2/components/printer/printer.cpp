#include <stdio.h>
#include "printer.h"

namespace ovning_2
{
    int func()
    {
        return 2;
    }
    int printNumbers(int start, int stop)
    {
        while (start != stop+1){
            PRINTF_COLOR(ANSI_BHCYAN, "%d" NEW_LINE, start);
            start ++;
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        return 0;
    }
}
