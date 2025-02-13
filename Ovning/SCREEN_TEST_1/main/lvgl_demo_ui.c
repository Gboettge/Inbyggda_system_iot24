/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void MyTimer()
{
vTaskDelay(pdTICKS_TO_MS(1000));
}

void example_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    lv_obj_t *label = lv_label_create(scr);
    lv_obj_t *label1 = lv_label_create(scr);
    lv_obj_t *label2 = lv_label_create(scr);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL); /* Circular scroll */
    lv_label_set_text(label, "Hej baby");

    lv_label_set_long_mode(label1, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    lv_label_set_text(label1, "Jag kommer inte hem till middag...");
   
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL); /* Circular scroll */
    lv_label_set_text(label2, "Ok? <3");
    /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
    lv_obj_set_width(label, disp->driver->hor_res);
    lv_obj_set_width(label1, disp->driver->hor_res);
    lv_obj_set_width(label2, disp->driver->hor_res);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(label2, LV_ALIGN_BOTTOM_MID, 0, 0);
}
