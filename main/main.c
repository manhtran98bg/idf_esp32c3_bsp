/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"

#include "app_manager.h"
static const char * TAG = "app_main";
static void print_heap_remain(void * param) {
    while (1) {
        ESP_LOGI(TAG,"Free heap size %u", esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void app_main(void)
{
    xTaskCreate(print_heap_remain, "print_heap_remain", 2048, NULL, 1, NULL);
    ESP_ERROR_CHECK(app_manager_init());
}
