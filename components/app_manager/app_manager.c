#include "app_manager.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#include "bsp/esp-bsp.h"

#include "esp_timer.h"

static const char *TAG = "app_manager";

static void gif_task(void *pvParameters)
{
    int delayMs = 0;
    while (true)
    {
        // if (esp_GIF_openFile("/littlefs/gif/1.gif"))
        // {
        //     int64_t t0 = esp_timer_get_time();
        // 	while (esp_GIF_playFrame(&delayMs, NULL)) {
        //     }
        //     int64_t t1 = esp_timer_get_time();
        //     ESP_LOGI("GIF", "Decode+draw = %lld us", t1 - t0);
        // 	esp_GIF_close();
        // }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
#include "sdkconfig.h"
esp_err_t app_manager_init(void)
{
    ESP_LOGI(TAG, "Initializing...");

    lv_display_t *display = bsp_display_start();
    bsp_littlefs_mount();
    /* Wait until other tasks finish screen operations */
    bsp_display_lock(0);
    lv_obj_t *screen = lv_disp_get_scr_act(display);
    lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    // create gif
    // lv_obj_t *gif;
    // gif = lv_gif_create(screen);
    // lv_gif_set_color_format(gif, LV_COLOR_FORMAT_RGB565);
    // lv_gif_set_src(gif, "A:/littlefs/gif/turn_right.gif");
    // lv_obj_center(gif);

    // lv_obj_t * lottie = lv_rlottie_create_from_file(screen, 30, 30, "/littlefs/lottie/turn_right.json");
    lv_obj_t * lottie = lv_lottie_create(lv_screen_active());
    lv_lottie_set_src_file(lottie, "/littlefs/lottie/turn_right.json");
    static uint8_t buf[60 * 60 * 4];
    lv_lottie_set_buffer(lottie, 60, 60, buf);
    lv_obj_center(lottie);
    /* Load the screen */
    // xTaskCreate(gif_task, "gif_task", 8192, NULL, configMAX_PRIORITIES - 1, NULL);
    lv_scr_load(screen);
    bsp_display_unlock();

    ESP_LOGI(TAG, "Initialized successfully.");
    return ESP_OK;
}
