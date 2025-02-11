#include "Button.h"


button_handle button_init(int pin, strapping_mode mode){

    button_handle new_button = malloc (sizeof(button));
    new_button->pin = pin;
    new_button->mode = mode;
    new_button->latch = 0;
    new_button->pressed = false;
    gpio_input_enable(pin);
    gpio_intr_disable(pin);
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
void update(button_handle button){
    button->pressed = gpio_get_level(button->pin); // tar inte bort debounce
    
    if (button->pressed && !button->latch){
        //button->pressed = true;
        button->latch = 1;
        printf("%d\n", button->pressed);
        return;
    }
    else if (!button->pressed && button->latch){
        //button->pressed = false;
        button->latch = 0;
        printf("%d\n", button->pressed);
        return;
    }
    //ingen vtask delay här
    
}

//ordna ifall man nyttjar pullup istäället för pullup
bool isPressed (button_handle button){
    return button->pressed;
}


// int init_button(pin, int x);

// int update(xxx);

// bool isPressed (int xxx);

// void setOnPressed ( void(*onPressed)(int pin));

