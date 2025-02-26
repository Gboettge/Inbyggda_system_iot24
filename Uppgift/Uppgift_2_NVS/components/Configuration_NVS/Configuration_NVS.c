#include <stdio.h>
#include "Configuration_NVS.h"


 myNvs_handle *nvs_init(){
    //myNvs_handle handle;
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    myNvs_handle * newNvs = malloc(sizeof(myNvs_handle));
    newNvs->deviceName ="";
    newNvs->serialNumber = "";
    //newNvs->handle = handle;
    return newNvs;
    
}

char* getDeviceName(myNvs_handle *nvs){
    size_t required_size;
    esp_err_t err;
    printf("%s\n", nvs->deviceName);
    err= nvs_get_str(nvs->handle, KEY_DEVICE_NAME, NULL, &required_size);
    ESP_ERROR_CHECK(err);
    if (err != ESP_OK)
    {
        // strcpy(nvs->deviceName, "ESP32_Default");
        ESP_LOGE(TAG, "Device name not found, using default: %s", nvs->deviceName);
        ESP_LOGE(TAG, "s: %d", err);

        // ESP_ERROR_CHECK(nvs_commit(nvs->handle));
        // ss
    }
    //char *deviceName = nvs->deviceName
    nvs->deviceName = malloc(required_size);
    if(nvs->deviceName == NULL){
        printf("Error");
    }

    err= nvs_get_str(nvs->handle, KEY_DEVICE_NAME, nvs->deviceName, &required_size);
    // nvs_get_str(my_handle, "server_name", NULL, &required_size);
    // nvs_get_str(my_handle, "server_name", server_name, &required_size);
    // char *deviceName = malloc(required_size);
    // if (!deviceName)
    // {
        //     ESP_LOGE(TAG, "Memory allocation failed");
        //     return NULL;
        // }
        
    return nvs->deviceName;
}

void setDeviceName(myNvs_handle *nvs, char * name){
    esp_err_t err = nvs_open("DeviceInfo", NVS_READWRITE, &nvs->handle); // <-- FIX: Använd nvs.handle
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open NVS namespace");
        return;
    }

    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_str(nvs->handle, KEY_DEVICE_NAME, name));
    nvs_commit(nvs->handle);
    ESP_LOGI(TAG, "Updated Device Name: %s", name);

    nvs_close(nvs->handle); 
}

void nvsDestroy(myNvs_handle *nvs){
    nvs_close(nvs->handle);
    nvs_flash_erase();
}
    
    
    // Stäng NVS efter användning
// char* getDeviceName(myNvs_handle nvs){
//     size_t required_size = STR_LENGHT;
//     char *deviceName = malloc(STR_LENGHT);
//     if (!deviceName)
//     {
//         ESP_LOGE(TAG, "Memory allocation failed");
//         return NULL;
//     }

//     esp_err_t err = nvs_get_str(nvs->handle, KEY_DEVICE_NAME, deviceName, &required_size);
//     if (err != ESP_OK)
//     {
//         strcpy(deviceName, "ESP32_Default");
//         ESP_LOGW(TAG, "Device name not found, using default: %s", deviceName);
//         nvs_set_str(nvs->handle, KEY_DEVICE_NAME, deviceName);
//         nvs_commit(nvs->handle);
//     }
//     return deviceName;
// }
// char* getSerialNumber(myNvs_handle nvs){

// }
// myNvs_handle setSerialNumber(char * number){
//     
// }


// nvs_handle nvs_init() {
//     esp_err_t err = nvs_flash_init();
//     if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//         ESP_ERROR_CHECK(nvs_flash_erase());
//         err = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(err);
//     ESP_ERROR_CHECK(nvs_open("nvs", NVS_READWRITE, &nvs->nvsHandle));

//     PRINTF_COLOR(ANSI_BLUE, "Successfully configured NVS default partition" NEW_LINE);

//     if (strcmp(nvs_getSerialNumber(nvs), "Not found") != 0) {
//         PRINTF_COLOR(ANSI_BLUE, "Serial number is set" NEW_LINE);
//         nvs->serialNumber = nvs_getSerialNumber(nvs);
//     } else {
//         PRINTF_COLOR(ANSI_YELLOW, "Serial number is not set!" NEW_LINE);
//     }

//     if (strcmp(nvs_getDeviceName(nvs), "Not found") != 0) {
//         PRINTF_COLOR(ANSI_BLUE, "Device name is set" NEW_LINE);
//         nvs->deviceName = nvs_getDeviceName(nvs);
//     } else {
//         PRINTF_COLOR(ANSI_YELLOW, "Device name is not set!" NEW_LINE);
//     }
// }

// char* nvs_getDeviceName(nvs_t* nvs) {
//     size_t required_size;
//     esp_err_t err = nvs_get_str(nvs->nvsHandle, KEY_DEVICE_NAME, NULL, &required_size);
//     if (err == ESP_OK) {
//         nvs->deviceName = (char*) malloc(required_size);
//         PRINTF_COLOR(ANSI_BLUE, "Retrieved successfully" NEW_LINE);
//         ESP_ERROR_CHECK(nvs_get_str(nvs->nvsHandle, KEY_DEVICE_NAME, nvs->deviceName, &required_size));
//         return nvs->deviceName;
//     } else if (err == ESP_ERR_NVS_NOT_FOUND) {
//         PRINTF_COLOR(ANSI_RED, "The device name not found on NVS" NEW_LINE);
//         return "Not found";
//     }
//     PRINTF_COLOR(ANSI_RED, "Unhandled error reading NVS" NEW_LINE);
//     return "Not found";
// }

// void nvs_setDeviceName(nvs_t* nvs, char* deviceName) {
//     ESP_ERROR_CHECK(nvs_set_str(nvs->nvsHandle, KEY_DEVICE_NAME, deviceName));
//     PRINTF_COLOR(ANSI_BLUE, "Successfully wrote key/value pair to NVS partition" NEW_LINE);
// }

// void nvs_setSerialNumber(nvs_t* nvs, char* serialNumber) {
//     ESP_ERROR_CHECK(nvs_set_str(nvs->nvsHandle, KEY_SERIAL_NUMBER, serialNumber));
//     PRINTF_COLOR(ANSI_BLUE, "Successfully wrote key/value pair to NVS partition" NEW_LINE);
// }

// char* nvs_getSerialNumber(nvs_t* nvs) {
//     size_t required_size;
//     esp_err_t err = nvs_get_str(nvs->nvsHandle, KEY_SERIAL_NUMBER, NULL, &required_size);
//     if (err == ESP_OK) {
//         PRINTF_COLOR(ANSI_BLUE, "Retrieved successfully" NEW_LINE);
//         nvs->serialNumber = (char*) malloc(required_size);
//         ESP_ERROR_CHECK(nvs_get_str(nvs->nvsHandle, KEY_SERIAL_NUMBER, nvs->serialNumber, &required_size));
//         return nvs->serialNumber;
//     } else if (err == ESP_ERR_NVS_NOT_FOUND) {
//         PRINTF_COLOR(ANSI_RED, "The serial number not found on NVS" NEW_LINE);
//         return "Not found";
//     }
//     PRINTF_COLOR(ANSI_RED, "Unhandled error reading NVS" NEW_LINE);
//     return "Not found";
// }
