#pragma once
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the entire application system
 *
 * This function performs all necessary system initializations required
 * for the application to start running properly.
 *
 * Includes:
 *  - Initializing the LVGL port and display interface
 *  - Initializing core services (display, UI, input devices, etc.)
 *  - Creating the main UI screen
 *
 * @return
 *  - ESP_OK on success
 *  - ESP_FAIL or other error codes on failure
 */
esp_err_t app_manager_init(void);

/**
 * @brief Main application loop
 *
 * This function runs the main application loop, responsible for
 * periodic LVGL task handling and UI refresh. It should typically
 * be called in the main task or a dedicated GUI task.
 *
 * It continuously calls `lv_timer_handler()` to allow LVGL to
 * update animations, process input, and refresh display contents.
 */
void app_manager_run(void);


#ifdef __cplusplus
}
#endif
