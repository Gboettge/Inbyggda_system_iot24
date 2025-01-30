#include <stdio.h>
#include "printer.h"

namespace ovning_2
{
    int func()
    {
        return 2;
    }
    void printNumbers(int start, int stop)
    {
        while (start != stop+1){
            PRINTF_COLOR(ANSI_BHCYAN, "%d" NEW_LINE, start);
            start ++;
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
    void takeTimeAndPrintEverySecond(int time)
    {
        int index = 0;
        int start = 0;
        int stop = 20;
        char * cyan = ANSI_HCYAN;
        char * yellow = ANSI_YELLOW;
        char * red = ANSI_RED;
        char * color[3] = {cyan, yellow, red};
        int result;

        while (start != stop+1){
            index = index % 3;
            result = time * time; 
            PRINTF_COLOR(color[index], "%d" NEW_LINE, time);
            time++;
            index++; 
            start++;
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

    }
    int multiply(int a, int b){
        return a * b;
    }
}
