#include <stdio.h>
#include "DISPLAY1.h"

display_s *display_init(){
    ESP_LOGI(TAG, "Initialize I2C bus");
        i2c_master_bus_handle_t i2c_bus = NULL;
        i2c_master_bus_config_t bus_config = {
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .i2c_port = I2C_BUS_PORT,
            .sda_io_num = EXAMPLE_PIN_NUM_SDA,
            .scl_io_num = EXAMPLE_PIN_NUM_SCL,
            .flags.enable_internal_pullup = true,
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus));
    
        ESP_LOGI(TAG, "Install panel IO");
        esp_lcd_panel_io_handle_t io_handle = NULL;
        esp_lcd_panel_io_i2c_config_t io_config = {
            .dev_addr = EXAMPLE_I2C_HW_ADDR,
            .scl_speed_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
            .control_phase_bytes = 1,               // According to SSD1306 datasheet
            .lcd_cmd_bits = EXAMPLE_LCD_CMD_BITS,   // According to SSD1306 datasheet
            .lcd_param_bits = EXAMPLE_LCD_CMD_BITS, // According to SSD1306 datasheet
   
            .dc_bit_offset = 6,                     // According to SSD1306 datasheet
   
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus, &io_config, &io_handle));
    
        ESP_LOGI(TAG, "Install SSD1306 panel driver");
        esp_lcd_panel_handle_t panel_handle = NULL;
        esp_lcd_panel_dev_config_t panel_config = {
            .bits_per_pixel = 1,
            .reset_gpio_num = EXAMPLE_PIN_NUM_RST,
        };
    
        esp_lcd_panel_ssd1306_config_t ssd1306_config = {
            .height = EXAMPLE_LCD_V_RES,
        };
        panel_config.vendor_config = &ssd1306_config;
        ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle));
   
    
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    
    #if CONFIG_EXAMPLE_LCD_CONTROLLER_SH1107
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
    #endif
    
        ESP_LOGI(TAG, "Initialize LVGL");
        const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
        lvgl_port_init(&lvgl_cfg);
    
        const lvgl_port_display_cfg_t disp_cfg = {
            .io_handle = io_handle,
            .panel_handle = panel_handle,
            .buffer_size = EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES,
            .double_buffer = true,
            .hres = EXAMPLE_LCD_H_RES,
            .vres = EXAMPLE_LCD_V_RES,
            .monochrome = true,
            .rotation = {
                .swap_xy = false,
                .mirror_x = false,
                .mirror_y = false,
            }
        };
        lv_disp_t *disp = lvgl_port_add_disp(&disp_cfg);
        lv_disp_set_rotation(disp, LV_DISP_ROT_NONE);
        display_s *newDisp =pvPortMalloc(sizeof(display_s));
        newDisp->disp = disp;
        
    /* Rotation of the screen */

    ESP_LOGI(TAG, "Display LVGL Scroll Text");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (lvgl_port_lock(0)) {
        // display_ui(disp);
        // Release the mutex
        lvgl_port_unlock();
        return newDisp;
    }
    return NULL;
}

void display_ui(display_s *display, char* newleftTop, char* newleftMid, char* newleftButtom, char* score, char* time)
{
    // lv_disp_remove(display->disp);
    lv_obj_t *scr = lv_disp_get_scr_act(display->disp);

    lv_obj_clean(scr);
   
    
    lv_obj_t *leftTop = NULL;
    lv_obj_t *leftCenter = NULL;
    lv_obj_t *leftBottom = NULL;
    lv_obj_t *rightTop = NULL;
    lv_obj_t *rightBottom = NULL;
    char newQ1[12];
    char newQ2[12];
    char newQ3[12];
    
    if(leftTop == NULL){
        // lv_screen_clean(leftTop);
        leftTop = lv_label_create(scr);
        lv_label_set_long_mode(leftTop, LV_LABEL_LONG_SCROLL); /* Circular scroll */
        lv_obj_set_width(leftTop, display->disp->driver->hor_res/2);
        lv_obj_align(leftTop, LV_ALIGN_TOP_LEFT, 0, 0);
    }
    if(leftCenter == NULL){
        leftCenter = lv_label_create(scr);
        lv_label_set_long_mode(leftCenter, LV_LABEL_LONG_SCROLL); /* Circular scroll */
        lv_obj_set_width(leftCenter, display->disp->driver->hor_res/2); 
        lv_obj_align(leftCenter, LV_ALIGN_LEFT_MID, 0, 0);
    }
    if(leftBottom == NULL){
        leftBottom = lv_label_create(scr);
        lv_label_set_long_mode(leftBottom, LV_LABEL_LONG_SCROLL); /* Circular scroll */
        lv_obj_set_width(leftBottom, display->disp->driver->hor_res/2);
        lv_obj_align(leftBottom, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    }
    if(rightTop == NULL){
        rightTop = lv_label_create(scr);
        lv_label_set_long_mode(rightTop, LV_LABEL_LONG_SCROLL); /* Circular scroll */
        lv_obj_set_width(rightTop, display->disp->driver->hor_res/3);   
        lv_obj_align(rightTop, LV_ALIGN_TOP_RIGHT, 0, 0);
    }
    if(rightBottom == NULL){
        rightBottom = lv_label_create(scr);
        lv_label_set_long_mode(rightBottom, LV_LABEL_LONG_SCROLL); /* Circular scroll */
        lv_obj_set_width(rightBottom, display->disp->driver->hor_res/4);
        lv_obj_align(rightBottom, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
       
    }
    
    if(newleftTop == NULL){
        newleftTop = " ";
    }
    else{
        strcpy(newQ1, "1: ");
        strcat(newQ1, newleftTop);
    }
    if(newleftMid == NULL){
        newleftMid = " ";
    }
    else{
        strcpy(newQ2, "2: ");
        strcat(newQ2, newleftMid);
    }
    if(newleftButtom == NULL){
        newleftButtom = " ";
    }
    else{
        strcpy(newQ3, "3: ");
        strcat(newQ3, newleftButtom);
    }
    if(score == NULL){
        score = " ";
    }
    
    if(time == NULL){
        time = " ";
    }
    
    
    
    
    lv_label_set_text(leftTop, newQ1);
    lv_label_set_text(leftCenter, newQ2);
    lv_label_set_text(leftBottom, newQ3);
    lv_label_set_text(rightTop, score);
    lv_label_set_text(rightBottom, time);
    // lv_obj_t *label = lv_label_create(scr);
    // lv_obj_t *label1 = lv_label_create(scr);
    // lv_obj_t *label2 = lv_label_create(scr);
    // lv_label_set_text(label, "Hej baby");
    // lv_label_set_long_mode(label1, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    // lv_label_set_text(label1, "Jag kommer inte hem till middag...");
    
    // //lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL); /* Circular scroll */
    // lv_label_set_text(label2, "Ok? <3");
    // /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
    // // lv_obj_set_width(label, disp->driver->hor_res);
    // lv_obj_set_width(label, display->disp->driver->hor_res);
    // lv_obj_set_width(label1, display->disp->driver->hor_res);
    // lv_obj_set_width(label2, display->disp->driver->hor_res);
    // lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    // lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(label2, LV_ALIGN_BOTTOM_MID, 0, 0);
}
