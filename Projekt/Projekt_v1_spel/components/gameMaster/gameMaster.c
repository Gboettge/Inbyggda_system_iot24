#include "gameMaster.h"


gm_handle gm_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb, guess_color_handle guess_color){
    gm_handle newGame = pvPortMalloc(sizeof(gm));
    newGame->bLedOne = bLedOne;
    newGame->bLedTwo = bLedTwo;
    newGame->bLedThree = bLedThree;
    newGame->btnOne = btnOne;
    newGame->btnTwo = btnTwo;
    newGame->btnThree = btnThree;
    newGame->display = display;
    newGame->rgb = rgb;
    newGame->previousState = GM_NONE;
    newGame->currentState = GM_START;
    newGame->gameRunning = false;
    return newGame;
}


void gm_init_games(gm_handle gm){
    gm->guess_color = guess_color_init(gm->btnOne, gm->btnTwo, gm->btnThree, gm->bLedOne, gm->bLedTwo, gm->bLedThree, gm->display, gm->rgb);
}

void gm_free_games(gm_handle gm){
    vPortFree(gm->guess_color);
}

void gm_update(gm_handle gm){
    // if (gm->currentState != gm->previousState);
        TickType_t current_tick = xTaskGetTickCount();
        // printf("1\n");
        switch (gm->currentState)
        {
            case GM_START:
            if(gm->previousState != gm->currentState){
                gm->previousTick = current_tick;
                display_update(gm->display, "START");
                setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
                // break;
            }

            if (current_tick - gm->previousTick >= pdMS_TO_TICKS(3000)){
                gm->nextState = GM_GAME;
                gm->previousTick = current_tick;
            }
            else{
                gm->nextState = gm->currentState;
            }
            /* code */
            break;
            
            case GM_GAME:
            if(gm->previousState != gm->currentState){
                gm_init_games(gm);
                gm->previousTick = current_tick;
                // break;
            }
            gm->gameRunning = guess_color_play(gm->guess_color);
            if(gm->gameRunning){
                gm->nextState = gm->currentState;
            }
            else{
                gm->nextState = GM_GAMEOVER;
                gm->previousTick = current_tick;
            }
            // if(gm->previousState != gm->currentState){
            //     display_update(gm->display, "Game");
            //     guess_color_play(gm->guess_color);
            //     setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
            // }
            // if (current_tick - gm->previousTick >= pdMS_TO_TICKS(3000)){
            //     gm->nextState = GM_GAMEOVER;
            //     gm->previousTick = current_tick;
            // }
            // else{
            //     gm->nextState = gm->currentState;
            // }
            break;
            
            
            case GM_GAMEOVER:
            if(gm->previousState != gm->currentState){
                //Börja här imorgon
                printf("Gameover\n");
                display_update(gm->display, "Game Over");
                gm->previousTick = current_tick;
                setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
                gm_free_games(gm);
                // break;
            }
            if (current_tick - gm->previousTick >= pdMS_TO_TICKS(3000)){
                gm->nextState = GM_START;
                gm->previousTick = current_tick;
            }
            else{
                gm->nextState = gm->currentState;
            }
            break;
            case GM_NONE:
            break;

        }
        gm->previousState = gm->currentState;
        gm->currentState = gm->nextState;            
        
    }


