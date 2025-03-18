#include "gameMaster.h"


gm_handle gm_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb){
    gm_handle newGame = pvPortMalloc(sizeof(gm_handle));
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
    return newGame;
}

void gm_update(gm_handle gm){
    // if (gm->currentState != gm->previousState);
        TickType_t current_tick = xTaskGetTickCount();
        // printf("1\n");
        switch (gm->currentState)
        {
            case GM_START:
            if(gm->previousState != gm->currentState){
                display_update(gm->display, "START");
                setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
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
                display_update(gm->display, "Game");
                setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
            }
            if (current_tick - gm->previousTick >= pdMS_TO_TICKS(3000)){
                gm->nextState = GM_GAMEOVER;
                gm->previousTick = current_tick;
            }
            else{
                gm->nextState = gm->currentState;
            }
            break;
            
            
            case GM_GAMEOVER:
            if(gm->previousState != gm->currentState){
                display_update(gm->display, "Game Over");
                setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
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


