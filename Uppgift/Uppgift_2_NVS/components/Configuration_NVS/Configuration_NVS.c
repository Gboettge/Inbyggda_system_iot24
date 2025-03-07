#include <stdio.h>
#include "Configuration_NVS.h"


myNvs_handle *nvs_init(){
    // vTaskDelay(pdMS_TO_TICKS(1000));
    nvs_handle_t handle;
    // ESP_ERROR_CHECK(nvs_flash_erase());          //för test
    esp_err_t err = nvs_flash_init();
    
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
        
    }
    ESP_ERROR_CHECK(err);
    err= nvs_open("Device info", NVS_READWRITE, &handle);
    if(err == ESP_ERR_NVS_NOT_FOUND || err == ESP_ERR_NVS_NOT_INITIALIZED){
        ESP_LOGI(TAG, "No key found");
    }
    myNvs_handle * newNvs = malloc(sizeof(myNvs_handle));

    size_t required_size;
    // char* newName;
    err = nvs_get_str(handle, KEY_DEVICE_NAME, NULL, &required_size);
    char *newName = malloc(required_size);
    nvs_get_str(handle, KEY_DEVICE_NAME, newName, &required_size);
    if(err != ESP_OK)
    {
        newNvs->deviceName = NULL;
    }
    else{
        newNvs->deviceName = newName;
        // free(newName);
    }
    
    err = nvs_get_str(handle, KEY_SERIAL_NUMBER, NULL, &required_size);
    char *newNumber = malloc(required_size);
    nvs_get_str(handle, KEY_SERIAL_NUMBER, newNumber, &required_size);
    if(err != ESP_OK)
    {
        newNvs->serialNumber = NULL;
    }
    else{
        newNvs->serialNumber = newNumber;
        //free(newNumber);
    }
    
    nvs_close(handle);
    // vTaskDelay(pdMS_TO_TICKS(500));
    return newNvs;
    
}

void setDeviceName(myNvs_handle *nvs, char * name){
    if(strlen(name) > STR_LENGTH){
        ESP_LOGI(TAG, "name is to long, using previous..");
        return;
    }
    size_t required_size;
    nvs_handle_t handle;
    // vTaskDelay(pdMS_TO_TICKS(1000));
    esp_err_t err;
    err = nvs_open("Device info", NVS_READWRITE, &handle);
    ESP_ERROR_CHECK(err);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open NVS namespace");
        return;
    }
    
    err = nvs_set_str(handle, KEY_DEVICE_NAME, name);
    nvs_get_str(handle, KEY_DEVICE_NAME, NULL, &required_size); // memcopy bättre för behöver inte hämta från nvs
    char *newName = malloc(sizeof(&required_size));
    nvs_get_str(handle, KEY_DEVICE_NAME, newName, &required_size);

    // nvs_find_key()
    
    free(nvs->deviceName);
    nvs->deviceName = newName;

    // vTaskDelay(pdMS_TO_TICKS(1000));
    
   
    nvs_commit(handle);

    ESP_LOGI(TAG, "Set device name: %s", name);

    nvs_close(handle);
}

void setSerialNumber(myNvs_handle *nvs, char *number)
{
    if(strlen(number) > STR_LENGTH){
        ESP_LOGI(TAG, "number is to long, using previous..");
        return;
    }
    size_t required_size;
    nvs_handle_t handle;
    
    esp_err_t err;
    err = nvs_open("Device info", NVS_READWRITE, &handle);
    ESP_ERROR_CHECK(err);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open NVS namespace");
        return;
    }
    
    // vTaskDelay(pdMS_TO_TICKS(1000));
    
    err = nvs_set_str(handle, KEY_SERIAL_NUMBER, number);
    nvs_get_str(handle, KEY_SERIAL_NUMBER, NULL, &required_size);
    char *newNumber = malloc(sizeof(&required_size));
    nvs_get_str(handle, KEY_SERIAL_NUMBER, newNumber, &required_size);
    // strlen(number);
    // strcpy(newNumber, number)
    free(nvs->serialNumber);
    nvs->serialNumber = newNumber;

    nvs_commit(handle);
    ESP_LOGI(TAG, "Set serial number: %s", number);

    nvs_close(handle);
}


char *getDeviceName(myNvs_handle *nvs)
{
    if(nvs->deviceName == NULL){
        ESP_LOGI(TAG,"No name set, using name: Default");
        return "Default";
    }
    return nvs->deviceName;
    // printf("test: %s\n", nvs->deviceName);
}

char* getSerialNumber(myNvs_handle *nvs){
    if(nvs->serialNumber == NULL){
        ESP_LOGI(TAG,"No serial number, using number: 0");
        return "0";
    }
    // printf("test: \033[0;36m%s\n\033[0m", nvs->serialNumber);
    return nvs->serialNumber;
}

void nvsErase(){
    nvs_flash_erase();
}
void nvsFree(myNvs_handle *nvs){
    
    free(nvs->deviceName);
    free(nvs->serialNumber);
    nvs->deviceName = NULL;
    nvs->serialNumber = NULL;
}
