#pragma once
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <string.h>


#define MAX_PARAM_LENGTH 32
#define STR_LENGHT 16
#define KEY_DEVICE_NAME "keyDevice"
#define KEY_SERIAL_NUMBER "keySerial"

static const char * TAG = "NVS";

typedef struct {
        char* deviceName;
        char* serialNumber;
        nvs_handle_t handle;
    } myNvs_handle;

// typedef myNvs_t* myNvs_handle;

myNvs_handle *nvs_init();

char* getDeviceName(myNvs_handle *nvs);
char* getSerialNumber(myNvs_handle nvs);
void setDeviceName(myNvs_handle *nvs, char * name);
void setSerialNumber(char * number);

void nvsDestroy(myNvs_handle *nvs);






// // Initiera NVS och ladda parametrar
// esp_err_t myNvs_init(nvs_handle nvs) {
//     esp_err_t err = nvs_flash_init();
//     if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//         nvs_flash_erase();
//         err = nvs_flash_init();
//     }
//     if (err != ESP_OK) return err;

//     err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &nvs->nvsHandle);
//     if (err != ESP_OK) return err;

//     size_t length = MAX_PARAM_LENGTH;
//     nvs_get_str(nvs->nvsHandle, KEY_DEVICE_NAME, nvs->deviceName, &length);
//     length = MAX_PARAM_LENGTH;
//     nvs_get_str(nvs->nvsHandle, KEY_SERIAL_NUMBER, nvs->serialNumber, &length);

//     return ESP_OK;
// }

// // Returnera device name
// const char* myNvs_getDeviceName(nvs_handle nvs) {
//     return nvs->deviceName;
// }

// // Returnera serial number
// const char* myNvs_getSerialNumber(nvs_handle nvs) {
//     return nvs->serialNumber;
// }

// // Sätt och spara device name
// esp_err_t myNvs_setDeviceName(nvs_handle nvs, const char *name) {
//     if (strlen(name) >= MAX_PARAM_LENGTH) return ESP_ERR_INVALID_SIZE;
//     strcpy(nvs->deviceName, name);

//     esp_err_t err = nvs_set_str(nvs->nvsHandle, KEY_DEVICE_NAME, nvs->deviceName);
//     if (err == ESP_OK) err = nvs_commit(nvs->nvsHandle);

//     return err;
// }

// // Sätt och spara serial number
// esp_err_t myNvs_setSerialNumber(nvs_handle nvs, const char *serial) {
//     if (strlen(serial) >= MAX_PARAM_LENGTH) return ESP_ERR_INVALID_SIZE;
//     strcpy(nvs->serialNumber, serial);

//     esp_err_t err = nvs_set_str(nvs->nvsHandle, KEY_SERIAL_NUMBER, nvs->serialNumber);
//     if (err == ESP_OK) err = nvs_commit(nvs->nvsHandle);

//     return err;
// }

// // Hämta NVS-handle
// nvs_handle_t myNvs_getNvsHandle(nvs_handle nvs) {
//     return nvs->nvsHandle;
// }