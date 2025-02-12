#include "Button.h"



button_handle button_init(int pin, strapping_mode mode){

    button_handle new_button = malloc (sizeof(button));
    new_button->pin = pin;
    new_button->mode = mode;
    new_button->latch = 0;
    new_button->pressed = false;
    new_button->onpressed = NULL;
    gpio_input_enable(pin);
    gpio_intr_disable(pin);

    new_button->current_state = STATE_OFF;
    new_button->next_state = STATE_OFF;
    new_button->previous_state = STATE_OFF;
    new_button->level = 0;
    new_button->debounce_tick = 0;
    
    if(mode == GPIO_PULLUP){
        gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
    }
    else if(mode == GPIO_PULLDOWN){
        gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
    }
    return new_button;
}

//debounce (latch?)
// 10ms max per uppdatering
void button_update(button_handle button)
{
    TickType_t current_tick = xTaskGetTickCount();
    if (button->mode == GPIO_PULLDOWN)
        button->level = gpio_get_level(button->pin); // tar inte bort debounce
    if (button->mode == GPIO_PULLUP)
        button->level = !gpio_get_level(button->pin);
    
    switch (button->current_state)
    {

    case STATE_ON:
        button->pressed = 1;
        if (button->level == 0)
        {
            button->next_state = DEBOUNCE_STATE_ON;
            button->debounce_tick = current_tick;
        }
        break;
    case DEBOUNCE_STATE_ON:
        button->pressed = 0;
        if (current_tick - button->debounce_tick >= pdMS_TO_TICKS(30))
        {
            button->next_state = STATE_OFF;
            if (button->onpressed != NULL)
            {
                button->onpressed(button->pin);
            }
            else {
                printf("pressed %d\n", button->pressed);
            }
        }
        break;
    case STATE_OFF:
        button->pressed = 0;
        if (button->level == 1)
        {
            button->next_state = DEBOUNCE_STATE_OFF;
            button->debounce_tick = current_tick;
        }
        break;
    case DEBOUNCE_STATE_OFF:
        button->pressed = 1;
        if (current_tick - button->debounce_tick >= pdMS_TO_TICKS(30))
        {
            button->next_state = STATE_ON;
        }
        break;
    default:
        printf("error %d\n", button->current_state);
        break;
    }
    if(button->next_state != button->current_state){
        printf("%d -> %d\n", button->current_state, button->next_state);
    }
    button->previous_state = button->current_state;
    button->current_state = button->next_state;
}
   
bool button_isPressed (button_handle button){
    return button->pressed;
}

void button_setOnPressed (button_handle button, void(*onPressed)(int pin)){
    button->onpressed = onPressed;
}

void button_print_press_num (int pin){
    printf ("Button: %d pressed\n", pin);
}

void button_print_num_x_ten(int pin){
    printf ("Button: %d x 10 = %d\n", pin, pin * 10);
}


// int init_button(pin, int x);

// int update(xxx);

// bool isPressed (int xxx);

// void setOnPressed ( void(*onPressed)(int pin));
/*
moving average filter (mjukvaru filter)
lista
index
adc värde
*/


/*
void button_update(button_handle button)
{
    TickType_t startTick = xTaskGetTickCount();

    if (button->mode == GPIO_PULLDOWN)
        button->pressed = gpio_get_level(button->pin); // tar inte bort debounce
    if (button->mode == GPIO_PULLUP)
    {
        button->pressed = !gpio_get_level(button->pin);
        // button->pressed = false;
        // button->latch = 1;
    }

    if (button->pressed && !button->latch)
    {
        TickType_t tickDifference = xTaskGetTickCount() - startTick;
        if (tickDifference >= pdMS_TO_TICKS(200))
        {
            button->latch = 1;
            button->pressed = true;
        }

        if (button->onpressed != NULL)
            button->onpressed(button->pin);
        else
            printf("pressed %d\n", button->pressed);
        return;
    }
    else if (!button->pressed && button->latch)
    {
        TickType_t tickDifference = xTaskGetTickCount() - startTick;

        if (tickDifference >= pdMS_TO_TICKS(200))
        {
        }
        button->latch = 0;
        button->pressed = false;
        //  printf("ticks passed: %ld\n", tickDifference);
        // printf("not pressed %d\n", button->pressed);
        return;
    }
    // ingen vtask delay här
    vTaskDelay(1);
    // printf("ticks passed: %ld\n", startTick);
    */

//ordna ifall man nyttjar pullup istäället för pullup