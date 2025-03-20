#include "gameMaster.h"

gm_handle gm_init(button_handle btnOne, button_handle btnTwo, button_handle btnThree, b_led_handle bLedOne, b_led_handle bLedTwo, b_led_handle bLedThree, display_handle display, RGB_handle rgb, guess_color_handle guess_color)
{
    gm_handle newGame = pvPortMalloc(sizeof(gm));
    newGame->bLedOne = bLedOne;
    newGame->bLedTwo = bLedTwo;
    newGame->bLedThree = bLedThree;
    newGame->btnOne = btnOne;
    newGame->btnTwo = btnTwo;
    newGame->btnThree = btnThree;
    newGame->display = display;
    newGame->rgb = rgb;

    newGame->previousState = GM_CYCLE_COLORS;
    newGame->currentState = GM_MENU;
    newGame->gameRunning = false;
    newGame->score = 0;
    newGame->seconds = MAX_COLORS;
    newGame->choise = 0;
    newGame->firstTime = true;

    
    return newGame;
}

void gm_update(gm_handle gm)
{
    // if (gm->currentState != gm->previousState);
    TickType_t current_tick = xTaskGetTickCount();
    // printf("1\n");
    switch (gm->currentState)
    {
        case GM_MENU:
        if(gm->firstTime){
            gm_init_games(gm);
            button_setOnPressed(gm->btnOne, gm_choise_one, (void *)gm);
            button_setOnPressed(gm->btnTwo, gm_choise_two, (void *)gm);
            button_setOnPressed(gm->btnThree, gm_choise_three, (void *)gm);
            gm->firstTime = false;
        }
        if (gm->previousState != gm->currentState)
        {
            gm->previousTick = current_tick;
            if (gm->display != NULL) {
                printf("Clearing display\n");
                // display_clear(gm->display); // Rensa displayen innan uppdatering
            } else {
                printf("Display is NULL\n");
            }
            display_update_fullscreen(gm->display, "Play", "Highscore", "Show RGB", NULL, NULL, NULL);
            setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
            printf("Menu state\n ");
            // break;
        }
        if (gm->choise != 0 && !gm->gameRunning)
        {
            if (gm->choise == 1)
            {
                gm->nextState = GM_GAME;
            }
            if (gm->choise == 2)
            {
                gm->nextState = GM_HIGHSCORE;
            }
            if (gm->choise == 3)
            {
                gm->nextState = GM_CYCLE_COLORS;
            }
            gm->choise = 0;
            break;
        }
        gm->nextState = gm->currentState;
        /* code */
        break;

    case GM_GAME:
        if (gm->previousState != gm->currentState)
        {
            // gm_init_games(gm);
            gm->previousTick = current_tick;
            // break;
        }
        gm->gameRunning = guess_color_play(gm->guess_color);
        if (gm->gameRunning)
        {
            gm->nextState = gm->currentState;
        }
        else
        {
            gm->nextState = GM_NONE;
            gm->gameRunning = false;
            gm->previousTick = current_tick;
            // gm_free_games(gm);

            // gm->display = display_init();
        }

        break;

    case GM_HIGHSCORE:
        if (gm->previousState != gm->currentState)
        {
            // Börja här imorgon
            printf("Highscore\n");
            display_update_fullscreen(gm->display, "Highscore:", NULL, "1: Back", "0", NULL, NULL);
            gm->previousTick = current_tick;
            // setRGB(gm->rgb, colors[gm->currentState].red, colors[gm->currentState].green, colors[gm->currentState].blue);
            // break;
        }
        if (gm->choise == 1)
        {
            gm->nextState = GM_MENU;
            gm->choise = 0;
        }
        else
        {
            gm->nextState = gm->currentState;
        }
        break;
    case GM_CYCLE_COLORS:
        if (gm->previousState != gm->currentState)
        {
            display_update_fullscreen(gm->display, "COLOR", NULL, "1: Back", NULL, NULL, NULL);
        }
        if (gm->choise == 1)
        {
            gm->nextState = GM_MENU;
            gm->choise = 0;
        }
        else
        {
            gm->nextState = gm->currentState;
        }
        break;
    case GM_NONE:
        gm->choise = 0;
        gm->firstTime = true; //NY
        gm->nextState = GM_MENU;
    }
    gm->previousState = gm->currentState;
    gm->currentState = gm->nextState;
}

void gm_init_games(gm_handle gm)
{
    gm->guess_color = guess_color_init(gm->btnOne, gm->btnTwo, gm->btnThree, gm->bLedOne, gm->bLedTwo, gm->bLedThree, gm->display, gm->rgb);
}

void gm_free_games(gm_handle gm)
{
    vPortFree(gm->guess_color);
}

void gm_choise_one(int pin, void *arg)
{
    gm_handle gm = (gm_handle)arg;
    gm->choise = 1;
    printf("%d gm", gm->choise);
    // h->currentState = GUESS_COLOR_GENERATE_NEW;
}
void gm_choise_two(int pin, void *arg)
{
    gm_handle gm = (gm_handle)arg;
    gm->choise = 2;
    printf("%d gm", gm->choise);
    // h->lives--;
}
void gm_choise_three(int pin, void *arg)
{
    gm_handle gm = (gm_handle)arg;
    gm->choise = 3;
    printf("%d gm" , gm->choise);
    // h->lives = 3;
}