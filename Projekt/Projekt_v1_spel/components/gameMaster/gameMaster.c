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

    newGame->guess_color = guess_color;

    newGame->previousState = GM_CYCLE_COLORS;
    newGame->currentState = GM_MENU;
    newGame->gameRunning = false;
    newGame->score = 0;
    newGame->seconds = MAX_COLORS;
    newGame->choise = 0;
    newGame->firstTime = true;
    newGame->colorCycle = 0;

    
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
            setRGB(gm->rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
            button_setOnPressed(gm->btnOne, gm_choise_one, (void *)gm);
            button_setOnPressed(gm->btnTwo, gm_choise_two, (void *)gm);
            button_setOnPressed(gm->btnThree, gm_choise_three, (void *)gm);
            gm->firstTime = false;
        }
        if (gm->previousState != gm->currentState)
        {
            gm->previousTick = current_tick;
            if (gm->display == NULL) {
                // printf("Clearing display\n");
                printf("Display is NULL\n");
                gm->display = display_init();
            }
            display_update_fullscreen(gm->display, "1: Play", "2: Highscore", "3: Show RGB", NULL, NULL, NULL);
            printf("Menu state\n ");
            
            printf("Display state: %p\n", gm->display);

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
            gm_init_games(gm);
            gm->previousTick = current_tick;
            // break;
        }
        gm->gameRunning = guess_color_play(gm->guess_color); //Går in i valt spel
        if (gm->gameRunning)
        {
            gm->nextState = gm->currentState;
        }
        else
        {
            gm->nextState = GM_NONE;
            gm->gameRunning = false;
            gm->previousTick = current_tick;
            gm_free_games(gm);
        }

        break;

    case GM_HIGHSCORE:
        if (gm->previousState != gm->currentState)
        {
            if(gm->score > 0){
                char myScore[12];
                snprintf(myScore, sizeof(myScore), "%d", gm->score);
                // Börja här imorgon
                // printf("Highscore\n");
                display_update_fullscreen(gm->display, "Highscore:", NULL, "1: Back", myScore, NULL, NULL);
                gm->previousTick = current_tick;
            }
            else{
                display_update_fullscreen(gm->display, "No hiscore", "Go play", "1: Back", NULL, NULL, NULL);

            }
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
        if(current_tick - gm->previousTick >= pdMS_TO_TICKS(3000)){
            setRGB(gm->rgb, colors[gm->colorCycle].red, colors[gm->colorCycle].green, colors[gm->colorCycle].blue);
            display_update_fullscreen(gm->display, color_names[gm->colorCycle], NULL, "1: Back", NULL, NULL, NULL);
            gm->colorCycle ++;
            gm->previousTick = current_tick;
            if (gm->colorCycle >= MAX_COLORS){
                gm->colorCycle = 0;
            }
        }

        if (gm->choise == 1)
        {
            gm->nextState = GM_MENU;
            setRGB(gm->rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
            gm->choise = 0;
        }
        else
        {
            gm->nextState = gm->currentState;
        }
        break;
    case GM_NONE:
    gm->choise = 0;
    gm->firstTime = true;
    gm_get_guess_highscore(gm);
    display_recreate(gm->display);
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
    // printf("%d gm\n", gm->choise);
}
void gm_choise_two(int pin, void *arg)
{
    gm_handle gm = (gm_handle)arg;
    gm->choise = 2;
    // printf("%d gm\n", gm->choise);
}
void gm_choise_three(int pin, void *arg)
{
    gm_handle gm = (gm_handle)arg;
    gm->choise = 3;
    // printf("%d gm\n" , gm->choise);
}

void gm_get_guess_highscore(gm_handle gm){
    int highscore = gm->guess_color->score;
    printf("Prev score: %d\n", highscore);
    if(highscore > gm->score){
        gm->score = highscore;
    }
}
// gammal GM_NONE
// printf("GM_NONE Display state: %p\n", gm->display);
// ESP_LOGI(TAG, "Trying to update display after returning to gameMaster...");
// gm->display = gm->guess_color->display;
// lv_disp_flush_ready(gm->display);
// free(gm->guess_color->display);
// free(gm->display->disp);
// free(gm->display->leftTop);
// free(gm->display->leftCenter);
// free(gm->display->leftBottom);
// free(gm->display->rightTop);
// free(gm->display->rightCenter);
// free(gm->display->rightBottom);

// printf("Free success\n");
// vTaskDelay(pdMS_TO_TICKS(2000));

// gm->display = display_init();
// printf("init success\n");
// vTaskDelay(pdMS_TO_TICKS(2000));
// if (lvgl_port_lock(0)) {
//     // display_ui(disp);
//     // Release the mutex
    // lvgl_port_unlock();

    //gm->disp_cfg.panel_handle = gm->panel_handle;

// if (gm->display != NULL) {
//     printf("Resetting display\n");
//     esp_lcd_panel_reset(gm->display->panel_handle);
//     esp_lcd_panel_init(gm->display->panel_handle);
//     esp_lcd_panel_disp_on_off(gm->display->panel_handle, true);
// } else {
//     printf("Display is NULL\n");
//     gm->display = display_init();
// }

// esp_lcd_panel_reset(gm->guess_color->display->panel_handle);
// esp_lcd_panel_init(gm->display->panel_handle);
// printf("Free success\n");
// vTaskDelay(pdMS_TO_TICKS(2000));
// esp_lcd_panel_disp_on_off(gm->display->panel_handle, true);
// printf("Free success\n");
// vTaskDelay(pdMS_TO_TICKS(2000));

// display_free(gm->display);
// printf("Free success\n");
// vTaskDelay(pdMS_TO_TICKS(2000));
// gm->display = display_init();
// printf("init success\n");
// vTaskDelay(pdMS_TO_TICKS(2000));

// esp_lcd_panel_reset(gm->display);
// esp_lcd_panel_init(gm->display);
// esp_lcd_panel_disp_on_off(gm->display, true);


// display_update(gm->guess_color->display, "Back in GameMaster!");
// vTaskDelay(pdMS_TO_TICKS(5000));
// printf("1\n");
// display_update(gm->display, "Back in GameMaster!");
// printf("2\n");
// display_reset(gm->display);