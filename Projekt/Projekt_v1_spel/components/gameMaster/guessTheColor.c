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

    newGame->previousState = GUESS_COLOR_GENERATE_NEW;
    newGame->currentState = GUESS_COLOR_START;

    newGame->lives = 3;
    newGame->choise = 0;
    newGame->correctPlacement = -1;
    newGame->score = 0;
    newGame->seconds = STARTUP_DURATION/1000;
    newGame->isGame = true;
    newGame->isWaiting = true;

    // button_setOnPressed(newGame->btnOne, button_choise_one, (void*)newGame);
    // button_setOnPressed(newGame->btnTwo, button_choise_two, (void*)newGame);
    // button_setOnPressed(newGame->btnThree, button_choise_three, (void*)newGame);

    return newGame;
}
bool guess_color_play(guess_color_handle g1)
{
    TickType_t currentTick = xTaskGetTickCount();
    if (currentTick - g1->secondsTick >= pdMS_TO_TICKS(1000))
    {
        g1->seconds--;
        g1->secondsTick = currentTick;
        char myInt[12];
        snprintf(myInt, sizeof(myInt), "%d", g1->seconds);
        char myScore[12];
        snprintf(myScore, sizeof(myScore), "%d", g1->score);
        display_update_time(g1->display, myInt);
        if (g1->currentState == GUESS_COLOR_START)
        {
            display_update_fullscreen(g1->display, "Wellcome", NULL, "Starts in:", NULL, NULL, myInt);
            // display_ui(g1->display, "Wellcome", NULL, "Starts in:", NULL, myInt);
        }
        if (g1->currentState == GUESS_COLOR_TIMES_UP){
            display_update_fullscreen(g1->display, "Time's up!", "Score:", "Return in:", NULL, myScore, myInt);
        }
        if (g1->currentState == GUESS_COLOR_GAMEOVER){
            display_update_fullscreen(g1->display, "Game Over 0 lives", "Score:", "Return in:", NULL, myScore, myInt);
        }
    }
    syncLives(g1);
    // printf("1\n");
    switch (g1->currentState)
    {
    case GUESS_COLOR_START:
        if (g1->previousState != g1->currentState)
        {
            // printf("state %d", g1->currentState);
            button_setOnPressed(g1->btnOne, button_choise_one, (void *)g1);
            button_setOnPressed(g1->btnTwo, button_choise_two, (void *)g1);
            button_setOnPressed(g1->btnThree, button_choise_three, (void *)g1);
            setRGB(g1->rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
            g1->previousTick = currentTick;
            // display_update(g1->display, "gameone start");

            // setRGB(g1->rgb, colors[g1->currentState].red, colors[g1->currentState].green, colors[g1->currentState].blue);
            // break;
        }

        if (currentTick - g1->previousTick >= pdMS_TO_TICKS(STARTUP_DURATION))
        {
            g1->seconds = PLAY_TIME;
            g1->nextState = GUESS_COLOR_GENERATE_NEW;
            g1->previousTick = currentTick;
        }
        else
        {
            g1->nextState = g1->currentState;
        }
        /* code */
        break;

    case GUESS_COLOR_GAME:
        if(g1->seconds <= 0){
            g1->nextState = GUESS_COLOR_TIMES_UP;
            break;
        }
        if (g1->isWaiting == false && currentTick - g1->previousTick >= pdMS_TO_TICKS(1500))
        {
            g1->nextState = GUESS_COLOR_GENERATE_NEW;
            g1->isWaiting = true;
            break;
        }
        if (g1->choise != 0 && g1->isWaiting == true)
        {

            if (g1->correctPlacement != 0)
            {
                char *answear;
                g1->previousTick = currentTick;
                if (g1->correctPlacement == g1->choise)
                {
                    g1->score++;
                    // ESP_LOGI(TAG, "Correct %d", choise);
                    answear = "Correct";
                }
                else
                {
                    // ESP_LOGI(TAG, "Wrong, answear was: %d", correctPlacement);
                    answear = "Wrong";
                    g1->lives--;
                    syncLives(g1);
                    if (g1->lives <= 0)
                    {
                        g1->nextState = GUESS_COLOR_GAMEOVER;
                    }
                }
                display_update(g1->display, answear);
                g1->choise = 0;
                g1->isWaiting = false;
            }
        }
        else
        {
            g1->nextState = g1->currentState;
        }
        break;

    case GUESS_COLOR_GENERATE_NEW:
        int myrandom = getRandom(currentTick, COLOR_SIZE);
        int *newRandoms = get_x_randoms(3, COLOR_SIZE, g1->previousTick);
        if (newRandoms != NULL)
        {
            ESP_LOGI(TAG, "Random: %d", newRandoms[0]);
            ESP_LOGI(TAG, "Random: %d", newRandoms[1]);
            ESP_LOGI(TAG, "Random: %d", newRandoms[2]);
        }
        else if (newRandoms == NULL)
        {
            ESP_LOGE(TAG, "Error");
            int *newRandoms = get_x_randoms(3, COLOR_SIZE, currentTick);
        }

        // if (i == 10)
        // {
        //     i = 0;
        // }
        vTaskDelay(pdMS_TO_TICKS(1));
        char scoreStr[12];
        char myInt[12];
        snprintf(scoreStr, sizeof(scoreStr), "%d", g1->score);
        snprintf(myInt, sizeof(myInt), "%d", g1->seconds);
        g1->previousTick = currentTick;
        int placement = newRandoms[0] + newRandoms[1] + newRandoms[2];
        vTaskDelay(pdMS_TO_TICKS(1));
        int newPlacement = getRandom(placement, 3);
        int zero = newRandoms[0];
        int one = newRandoms[1];
        int two = newRandoms[2];
        ESP_LOGI(TAG, "Placement: %d\n", newPlacement);
        ESP_LOGI(TAG, "randoms = %d, %d, %d\n", zero, one, two);
        setRGB(g1->rgb, colors[zero].red, colors[zero].green, colors[zero].blue);
        vTaskDelay(pdMS_TO_TICKS(1));
        if (newPlacement == 0)
        {
            display_ui(g1->display, color_names[zero], color_names[one], color_names[two], scoreStr, NULL, myInt);
            g1->correctPlacement = 1;
        }
        else if (newPlacement == 1)
        {
            display_ui(g1->display, color_names[two], color_names[zero], color_names[one], scoreStr, NULL, myInt);
            g1->correctPlacement = 2;
        }
        else if (newPlacement == 2)
        {
            display_ui(g1->display, color_names[one], color_names[two], color_names[zero], scoreStr, NULL, myInt);
            g1->correctPlacement = 3;
        }
        else
        {
            display_ui(g1->display, "Error", "Error", "color_names[zero]", scoreStr, NULL, myInt);
        }
        free(newRandoms);
        vTaskDelay(pdMS_TO_TICKS(1));
        // choise = 0;
        g1->nextState = GUESS_COLOR_GAME;

        break;
        case GUESS_COLOR_GAMEOVER:
        if (g1->previousState != g1->currentState)
        {
            setRGB(g1->rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
            b_led_setled(g1->bLedOne, BL_LIGHT_OFF);
            b_led_setled(g1->bLedTwo, BL_LIGHT_OFF);
            b_led_setled(g1->bLedThree, BL_LIGHT_OFF);
            
            g1->seconds = STARTUP_DURATION / 1000;
            
            // setRGB(g1->rgb, colors[g1->currentState].red, colors[g1->currentState].green, colors[g1->currentState].blue);
            g1->previousTick = currentTick;
            // break;
        }
        if (currentTick - g1->previousTick >= pdMS_TO_TICKS(STARTUP_DURATION))
        {
            display_clear(g1->display);
            g1->isGame = false;
            g1->nextState = GUESS_COLOR_START;
            g1->previousTick = currentTick;
        }
        else
        {
            g1->nextState = g1->currentState;
        }
        break;
        case GUESS_COLOR_TIMES_UP:
        if (g1->previousState != g1->currentState)
        {
            g1->seconds = STARTUP_DURATION / 1000;
            
            setRGB(g1->rgb, colors[OFF].red, colors[OFF].green, colors[OFF].blue);
            // b_led_blink(g1->bLedOne, 300, 300);
            // b_led_blink(g1->bLedTwo, 300, 300);
            // b_led_blink(g1->bLedThree, 300, 300);
            g1->previousTick = currentTick;
            // break;
        }
        if (currentTick - g1->previousTick >= pdMS_TO_TICKS(STARTUP_DURATION))
        {
            display_clear(g1->display);
            g1->isGame = false;
            g1->nextState = GUESS_COLOR_START;
            g1->previousTick = currentTick;
        }
        else
        {
            g1->nextState = g1->currentState;
        }
        break;
    }
    g1->previousState = g1->currentState;
    g1->currentState = g1->nextState;
    return g1->isGame;
}

void button_choise_one(int pin, void *arg)
{
    guess_color_handle h = (guess_color_handle)arg;
    h->choise = 1;
    printf("%d game choise" , h->choise);
    // h->currentState = GUESS_COLOR_GENERATE_NEW;
}
void button_choise_two(int pin, void *arg)
{
    guess_color_handle h = (guess_color_handle)arg;
    h->choise = 2;
    printf("%d game choise" , h->choise);
    // h->lives--;
}
void button_choise_three(int pin, void *arg)
{
    guess_color_handle h = (guess_color_handle)arg;
    h->choise = 3;
    printf("%d game choise" , h->choise);
    // h->lives = 3;
}

void syncLives(guess_color_handle g1)
{
    if (g1->lives == 3)
    {
        b_led_setled(g1->bLedOne, BL_LIGHT_ON);
        b_led_setled(g1->bLedTwo, BL_LIGHT_ON);
        b_led_setled(g1->bLedThree, BL_LIGHT_ON);
        // ESP_LOGI(TAG, "Lives: %d", g1->lives);
    }
    else if (g1->lives == 2)
    {
        // ESP_LOGI(TAG, "Lives: %d", g1->lives);
        b_led_setled(g1->bLedThree, BL_LIGHT_OFF);
        // b_led_update(g1->bLedThree);
        // vTaskDelay(pdMS_TO_TICKS(10));
    }
    else if (g1->lives == 1)
    {
        // ESP_LOGI(TAG, "Lives: %d", g1->lives);
        b_led_setled(g1->bLedTwo, BL_LIGHT_OFF);
        // b_led_update(g1->bLedTwo);
        // setRGB(g1->rgb, colors[4].red, colors[4].green, colors[4].blue);
        // vTaskDelay(pdMS_TO_TICKS(10));
    }
    else if (g1->lives <= 0)
    {
        // ESP_LOGI(TAG, "Lives: %d", g1->lives);
        b_led_setled(g1->bLedOne, BL_LIGHT_OFF);
        // b_led_update(g1->bLedOne);
        // setRGB(g1->rgb, colors[6].red, colors[6].green, colors[6].blue);
        // vTaskDelay(pdMS_TO_TICKS(10));
    }
}

int getRandom(int value, int modulu)
{
    int newval = value % modulu;

    return newval;
}
int *get_x_randoms(int returnAmount, int modulu, int tickcount)
{
    int *randoms = malloc(returnAmount * sizeof(int));
    vTaskDelay(pdMS_TO_TICKS(20));
    if (randoms == NULL)
    {
        return NULL; // Hantera minnesallokeringsfel
    }

    for (int i = 0; i < returnAmount; i++)
    {
        int random;
        int isUnique;
        
        do
        {
            isUnique = 1;
            random = (rand()+ tickcount) % modulu;
            for (int j = 0; j < i; j++)
            {
                if (random == randoms[j])
                {
                    // tickcount = rand();
                    isUnique = 0;
                    break;
                }
            }
        } while (!isUnique);
        randoms[i] = random;
        ESP_LOGI(TAG, "random adress; %p", &randoms[i]);
    }

    // int * tempRandoms = randoms;
    // free(randoms);
    // return tempRandoms;
    return randoms;
}