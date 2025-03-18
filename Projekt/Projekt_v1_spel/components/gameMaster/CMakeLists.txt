idf_component_register(SRCS "guessTheColor.c" "gameMaster.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver Button Binary_Led DISPLAY1 RGB_led_component)
