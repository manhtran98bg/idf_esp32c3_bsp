#include "app_manager.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#include "bsp/esp-bsp.h"
#include "lfs.h"
#include "littlefs_api.h"
#include "esp_littlefs.h"
#include "otto_emoji_gif.h"
#include "esp_animated_gif.h"
#include "esp_timer.h"
static const char *TAG = "app_manager";
extern const lv_image_dsc_t img_bulb_gif;

static void gif_task(void *pvParameters)
{
    int delayMs = 0;
	while (true)
	{
		if (esp_GIF_openFile("/littlefs/gif/1.gif"))
		{
            int64_t t0 = esp_timer_get_time();
			while (esp_GIF_playFrame(&delayMs, NULL)) {
            }
            int64_t t1 = esp_timer_get_time();
            ESP_LOGI("GIF", "Decode+draw = %lld us", t1 - t0);
			esp_GIF_close();
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

esp_err_t app_manager_init(void)
{
    ESP_LOGI(TAG, "Initializing...");

    lv_display_t *display = bsp_display_start();
    bsp_littlefs_mount();
    // bsp_esp_animated_gif_init();
    // bsp_lvgl_littlefs_mount();
    /* Wait until other tasks finish screen operations */
    // bsp_display_lock(0);
    // lv_obj_t *screen = lv_disp_get_scr_act(display);
    // lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    // lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    // /* Create a label */
    // lv_obj_t *label = lv_label_create(screen);
    // lv_label_set_text(label, "Hello");

    // /* Set text color to white */
    // lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);

    // /* Center the label */
    // lv_obj_center(label);

    //create gif
    // lv_obj_t * gif;
    // gif = lv_gif_create(screen);
    // lv_gif_set_color_format(gif, LV_COLOR_FORMAT_RGB565);
    // lv_gif_set_src(gif, &img_bulb_gif);
    // lv_gif_set_src(gif, &happy);
    // lv_gif_set_src(gif, "A:/gif/bulb.gif");
    /* Load the screen */
    xTaskCreate(gif_task, "gif_task", 8192, NULL, configMAX_PRIORITIES - 1, NULL);

    // lv_scr_load(screen);
    // bsp_display_unlock();

    ESP_LOGI(TAG, "Initialized successfully.");
    return ESP_OK;
}
