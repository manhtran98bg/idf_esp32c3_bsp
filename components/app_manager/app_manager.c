#include "app_manager.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#include "bsp/esp-bsp.h"

#include "esp_timer.h"
#include "ui.h"
static const char *TAG = "app_manager";

static void gif_task(void *pvParameters)
{
    int delayMs = 0;
    while (true)
    {
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
    ui_init();
    // lv_obj_t *screen = lv_disp_get_scr_act(display);
    // lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    // lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), LV_PART_MAIN);
    // lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    // create gif
    // lv_obj_t *gif;
    // gif = lv_gif_create(screen);
    // lv_gif_set_color_format(gif, LV_COLOR_FORMAT_RGB565);
    // lv_gif_set_src(gif, "A:/littlefs/gif/turn_right.gif");
    // lv_obj_center(gif);

    lv_obj_t *lottie = lv_lottie_create(lv_screen_active());
    lv_lottie_set_src_file(lottie, "/littlefs/lottie/turn_right.json");
    static uint8_t buf[30 * 30 * 4];
    lv_lottie_set_buffer(lottie, 30, 30, buf);

    Tvg_Matrix matrix = {
        -1, 0, 60,
        0, 1, 0,
        0, 0, 1};

    tvg_paint_set_transform(((lv_lottie_t *)lottie)->tvg_paint, &matrix);
    lv_anim_t *anim = lv_lottie_get_anim(lottie);
    lv_anim_set_duration(anim, 1050);
    lv_anim_set_reverse_delay(anim, 100);
    lv_anim_set_reverse_duration(anim, 1050);
    lv_obj_center(lottie);
    // /* Load the screen */

    // lv_scr_load(screen);
    bsp_display_unlock();

    ESP_LOGI(TAG, "Initialized successfully.");
    return ESP_OK;
}
