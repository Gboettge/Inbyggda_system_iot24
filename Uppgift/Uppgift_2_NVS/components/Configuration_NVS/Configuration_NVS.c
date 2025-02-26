#include <stdio.h>
#include "Configuration_NVS.h"


 myNvs_handle *nvs_init(){
    nvs_handle_t handle;
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
        
    }
    ESP_ERROR_CHECK(err);
    err= nvs_open(KEY_DEVICE_NAME, NVS_READWRITE, &handle);
    err= nvs_open(KEY_SERIAL_NUMBER, NVS_READWRITE, &handle);
    
    myNvs_handle * newNvs = malloc(sizeof(myNvs_handle));
//    // myNvs_handle *newNvs;

    newNvs->deviceName = "0";
    newNvs->serialNumber = "0";
    
    
    newNvs->handle = handle;
    
    nvs_set_str(handle, KEY_DEVICE_NAME, "None");
    nvs_commit(handle);
    nvs_set_str(handle, KEY_SERIAL_NUMBER, "0");
    nvs_commit(handle);
    return newNvs;
    
}

char* getDeviceName(myNvs_handle *nvs){
    
    size_t required_size = STR_LENGHT;
    esp_err_t err;
    

    err= nvs_get_str(nvs->handle, KEY_DEVICE_NAME, NULL, &required_size); 

    ESP_ERROR_CHECK(err);
   
    //err= nvs_get_str(nvs->handle, KEY_DEVICE_NAME, NULL, &required_size);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Device name not found, using default: %s", nvs->deviceName);
    }
    if(nvs->deviceName == NULL){
        printf("Error\n");
    }
    else{
        nvs->deviceName = malloc(required_size);
        err= nvs_get_str(nvs->handle, KEY_DEVICE_NAME, nvs->deviceName, &required_size);
    }
    //printf("test: %s\n", nvs->deviceName);
    return nvs->deviceName;
}

char* getSerialNumber(myNvs_handle *nvs){
    
    size_t required_size = STR_LENGHT;
    esp_err_t err;
    err= nvs_get_str(nvs->handle, KEY_SERIAL_NUMBER, NULL, &required_size);
    ESP_ERROR_CHECK(err);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Serial number not found, using default: %s", nvs->serialNumber);
    }
    if(nvs->serialNumber == NULL){
        printf("Error\n");
    }
    else{
        nvs->serialNumber = malloc(required_size);
        err= nvs_get_str(nvs->handle, KEY_SERIAL_NUMBER, nvs->serialNumber, &required_size);
    }
    //printf("test: \033[0;36m%s\n\033[0m", nvs->serialNumber);
    return nvs->serialNumber;
}

void setDeviceName(myNvs_handle *nvs, char * name){
    // esp_err_t err = nvs_open("DeviceInfo", NVS_READWRITE, &nvs->handle); // <-- FIX: Använd nvs.handle
    // if (err != ESP_OK)
    // {
    //     ESP_LOGE(TAG, "Failed to open NVS namespace");
    //     return;
    // }

    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_str(nvs->handle, KEY_DEVICE_NAME, name));
    nvs_commit(nvs->handle);
    ESP_LOGI(TAG, "Updated Device Name: %s", name);
}
void setSerialNumber(myNvs_handle *nvs, char * number){
    // esp_err_t err = nvs_open("DeviceInfo", NVS_READWRITE, &nvs->handle); // <-- FIX: Använd nvs.handle
    // if (err != ESP_OK)
    // {
    //     ESP_LOGE(TAG, "Failed to open NVS namespace");
    //     return;
    // }

    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_str(nvs->handle, KEY_SERIAL_NUMBER, number));
    nvs_commit(nvs->handle);
    ESP_LOGI(TAG, "Updated serial number: %s", number);
}

void nvsDestroy(){
    nvs_flash_erase();
}
void nvsClose(myNvs_handle *nvs){
    free(nvs);
    nvs_close(nvs->handle);
}
