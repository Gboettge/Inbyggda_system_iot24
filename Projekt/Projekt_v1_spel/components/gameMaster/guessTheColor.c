#include "guessTheColor.h"

guess_color_handle guess_color_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb){
    guess_color_handle newGame = pvPortMalloc(sizeof(guess_color_t));
    newGame->bLedOne = bLedOne;
    newGame->bLedTwo = bLedTwo;
    newGame->bLedThree = bLedThree;
    newGame->btnOne = btnOne;
    newGame->btnTwo = btnTwo;
    newGame->btnThree = btnThree;
    newGame->display = display;
    newGame->rgb = rgb;
    newGame->previousState = GUESS_COLOR_NONE;
    newGame->currentState = GUESS_COLOR_START;

    newGame->lives = 3;
    newGame->correctPlacement = -1;
    newGame->score = 0;
    newGame->seconds = 60;
    newGame->isGame = true;
    return newGame;
}
bool guess_color_play(guess_color_handle g1){

    TickType_t currentTick = xTaskGetTickCount();
    // printf("1\n");
    switch (g1->currentState)
        {
            case GUESS_COLOR_START:
            if(g1->previousState != g1->currentState){
                g1->previousTick = currentTick;
                display_update(g1->display, "gameone start");
                setRGB(g1->rgb, colors[g1->currentState].red, colors[g1->currentState].green, colors[g1->currentState].blue);
                // break;
            }

            if (currentTick - g1->previousTick >= pdMS_TO_TICKS(3000)){
                g1->nextState = GUESS_COLOR_GAME;
                g1->previousTick = currentTick;
            }
            else{
                g1->nextState = g1->currentState;
            }
            /* code */
            break;
            
            case GUESS_COLOR_GAME:
            if(g1->previousState != g1->currentState){
                display_update(g1->display, "Game one running");
                setRGB(g1->rgb, colors[g1->currentState].red, colors[g1->currentState].green, colors[g1->currentState].blue);
                g1->previousTick = currentTick;
                // break;
            }
            if (currentTick - g1->previousTick >= pdMS_TO_TICKS(6000)){
                g1->nextState = GUESS_COLOR_GAMEOVER;
                g1->previousTick = currentTick;
            }
            else{
                g1->nextState = g1->currentState;
            }
            break;
            
            
            case GUESS_COLOR_GAMEOVER:
            if(g1->previousState != g1->currentState){
                display_update(g1->display, "Gameone ending");
                setRGB(g1->rgb, colors[g1->currentState].red, colors[g1->currentState].green, colors[g1->currentState].blue);
                g1->previousTick = currentTick;
                // break;
            }
            if (currentTick - g1->previousTick >= pdMS_TO_TICKS(3000)){
                g1->isGame = false;
                g1->nextState = GUESS_COLOR_START;
                g1->previousTick = currentTick;
            }
            else{
                g1->nextState = g1->currentState;
            }
            break;

            case GUESS_COLOR_NONE:
            break;

        }
        g1->previousState = g1->currentState;
        g1->currentState = g1->nextState;            
        return g1->isGame;
    }