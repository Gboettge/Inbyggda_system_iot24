#include <stdio.h>
#include "DISPLAY1.h"

void app_main(void)
{

    display_s *lol = display_init();
    display_ui(lol, "hej", NULL, "då", "", "");
}