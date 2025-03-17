#include <stdio.h>
#include "RGB_led_component.h"
#include "button.h"
#include "DISPLAY1.h"
#include "Binary_Led.h"


int choise = 0;
b_led_handle bLed1;
b_led_handle bLed2;
b_led_handle bLed3;
RGB_handle rgb;
button_handle redBtn;
button_handle greenBtn;
button_handle blueBtn;
display_s *display;

//SNI koder
// lös så value 3 inte kan bli samma som value 1
int* get_x_randoms(int returnAmount, int modulu, int tickcount) {
    int* randoms = malloc(returnAmount * sizeof(int));
    vTaskDelay(pdMS_TO_TICKS(20));
    if (randoms == NULL) {
        return NULL; // Hantera minnesallokeringsfel
    }
    
    for (int i = 0; i < returnAmount; i++) {
        int random;
        int isUnique;
        do {
            isUnique = 1;
            random = tickcount % modulu;
            for (int j = 0; j < i; j++) {
                if (random == randoms[j]) {
                    tickcount = rand();
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


int getRandom(int value, int modulu)
{
    int newval = value % modulu;
    
    return newval;
}
void chooseOne();
void chooseTwo();
void chooseThree();
// läs värde från en pin, använd modulu(antalet alternativ) för att slumpa (0-4095)

void syncLives(int lives);
void app_main(void)
{
    gpio_reset_pin(16);
    gpio_reset_pin(17);
    gpio_reset_pin(5);
    bLed1 = b_led_init(16, BL_LIGHT_ON, false);
    bLed2 = b_led_init(17, BL_LIGHT_ON, false);
    bLed3 = b_led_init(5, BL_LIGHT_ON, false);
    redBtn = button_init(2, GPIO_PULLUP);
    greenBtn = button_init(3, GPIO_PULLUP);
    blueBtn = button_init(4, GPIO_PULLUP);
    display = display_init();
    // greenBtn = button_init(3, GPIO_PULLUP);
    // blueBtn = button_init(4, GPIO_PULLUP);
    rgb = rgb_init();
    setRGB(rgb, 55, 55, 55);
    int correctPlacement = 0;
    int score = 0;
    int i = -1;
    TickType_t previousSwitch = 0;
    button_setOnPressed(redBtn, chooseOne);
    button_setOnPressed(greenBtn, chooseTwo);
    button_setOnPressed(blueBtn, chooseThree);
    int lives = 3;
    while (1)
    {
        TickType_t currentTick = xTaskGetTickCount();
        
        syncLives(lives);
        updateRGB(rgb);
        button_update(redBtn);
        button_update(greenBtn);
        button_update(blueBtn);

        vTaskDelay(pdMS_TO_TICKS(40));
        // if (button_isPressed(redBtn))
        // {
        //     if (currentTick - previousSwitch >= pdMS_TO_TICKS(500))
        //     {
        if (choise != 0)
        {
            if (correctPlacement != 0)
            {
                if (correctPlacement == choise)
                {
                    score++;
                    ESP_LOGI(TAG, "Correct %d", choise);
                }
                else
                {
                    ESP_LOGI(TAG, "Wrong, answear was: %d", correctPlacement);
                    lives--;
                    syncLives(lives);
                    if (lives == 0)
                    {
                        ESP_LOGI(TAG, "Game Over");
                        break;
                    }
                }
            }
            i++;
            
            
            int myrandom = getRandom(currentTick, 10);
            int *newRandoms = get_x_randoms(3, 10, currentTick);
            if (newRandoms != NULL)
            {
                ESP_LOGI(TAG, "Random: %d", newRandoms[0]);
                ESP_LOGI(TAG, "Random: %d", newRandoms[1]);
                ESP_LOGI(TAG, "Random: %d", newRandoms[2]);
            }
            else if(newRandoms == NULL)
            {
                ESP_LOGE(TAG, "Error");
                int *newRandoms = get_x_randoms(3, 10, currentTick);
            }
            
            // if (i == 10)
            // {
            //     i = 0;
            // }
            vTaskDelay(pdMS_TO_TICKS(1));
            char scoreStr[12];
            char myInt[12];
            snprintf(scoreStr, sizeof(scoreStr), "%d", score);
            snprintf(myInt, sizeof(myInt), "%d", lives);
            previousSwitch = currentTick;
            int placement = newRandoms[0] + newRandoms[1] + newRandoms[2];
            vTaskDelay(pdMS_TO_TICKS(1));
            int newPlacement = getRandom(placement, 3);
            int zero = newRandoms[0];
            int one = newRandoms[1];
            int two = newRandoms[2];
            ESP_LOGI(TAG, "Placement: %d\n", newPlacement);
            ESP_LOGI(TAG, "randoms = %d, %d, %d\n", zero, one, two);
            setRGB(rgb, colors[zero].red, colors[zero].green, colors[zero].blue);
            vTaskDelay(pdMS_TO_TICKS(1));
            if (newPlacement == 0)
            {
                display_ui(display, color_names[zero], color_names[one], color_names[two], scoreStr, myInt);
                correctPlacement = 1;
                
                
            }
            else if (newPlacement == 1)
            {
                display_ui(display, color_names[two], color_names[zero], color_names[one], scoreStr, myInt);
                correctPlacement = 2;
                
            }
            else if (newPlacement == 2)
            {
                display_ui(display, color_names[one], color_names[two], color_names[zero], scoreStr, myInt);
                correctPlacement = 3;
            }
            else{
                display_ui(display, "Error", "Error", "color_names[zero]", scoreStr, myInt);
            }
            free(newRandoms);
            vTaskDelay(pdMS_TO_TICKS(1));
            choise = 0;
            
        }
        // display_ui(display, color_names[i], color_names[myrandom], color_names[(myrandom + 5) % 10], randomstr, myInt);
        // display_ui(display, color_names[i], color_names[myrandom], color_names[(myrandom + 5) % 10], randomstr, myInt);
        // ESP_LOGI(TAG, "%s", color_names[i]);

        
    }
    //     }
    //     // vTaskDelay(pdMS_TO_TICKS(1000));
    // }
}

void chooseOne(){
    choise = 1;
}
void chooseTwo(){
    choise = 2;
}
void chooseThree(){
    choise = 3;
}
void syncLives(int lives){
    if(lives == 3)
    {
        b_led_setled(bLed1, BL_LIGHT_ON);
        b_led_setled(bLed2, BL_LIGHT_ON);
        b_led_setled(bLed3, BL_LIGHT_ON);
    }
    else
    if (lives ==2)
    {
        b_led_setled(bLed1, BL_LIGHT_OFF);
        b_led_setled(bLed2, BL_LIGHT_ON);
        b_led_setled(bLed3, BL_LIGHT_ON);
    }
    else if (lives == 1)
    {
        b_led_setled(bLed1, BL_LIGHT_OFF);
        b_led_setled(bLed2, BL_LIGHT_OFF);
        b_led_setled(bLed3, BL_LIGHT_ON);
    }
    else if (lives == 0)
    {
        b_led_setled(bLed1, BL_LIGHT_OFF);
        b_led_setled(bLed2, BL_LIGHT_OFF);
        b_led_setled(bLed3, BL_LIGHT_OFF); 
    }
    b_led_update(bLed1);
    b_led_update(bLed2);
    b_led_update(bLed3);
}
