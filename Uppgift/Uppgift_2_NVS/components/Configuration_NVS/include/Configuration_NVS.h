#pragma once
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <string.h>


#define MAX_PARAM_LENGTH 32
#define STR_LENGTH 16
#define KEY_DEVICE_NAME "keyDevice"
#define KEY_SERIAL_NUMBER "keySerial"
#define NAMESPACE "Device info"

static const char * TAG = "NVS";

//fixa gemensam namespace
//hantera erase med hjälp av kolla om nyckeln finns

typedef struct {
        char* deviceName;
        char* serialNumber;
    } myNvs_handle;

// typedef myNvs_t* myNvs_handle;

myNvs_handle *nvs_init();

char* getDeviceName(myNvs_handle *nvs);
char* getSerialNumber(myNvs_handle *nvs);
void setDeviceName(myNvs_handle *nvs, char * name);
void setSerialNumber(myNvs_handle *nvs, char * number);

void nvsErase();
void nvsFree(myNvs_handle *nvs);

