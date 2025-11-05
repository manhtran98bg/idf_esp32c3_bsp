#include "app_manager.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#include "bsp/esp-bsp.h"
#include "lfs.h"
static const char *TAG = "app_manager";
lfs_t lfs;
lfs_file_t file;
esp_err_t app_manager_init(void)
{
    ESP_LOGI(TAG, "Initializing...");

    bsp_littlefs_mount();

    lv_display_t *display = bsp_display_start();
    // test lvgl
    // lvgl lfs

    const struct lfs_config cfg = {
        // block device operations
        .read = littlefs_esp_part_read,
        .prog = user_provided_block_device_prog,
        .erase = user_provided_block_device_erase,
        .sync = user_provided_block_device_sync,

        // block device configuration
        .read_size = 16,
        .prog_size = 16,
        .block_size = 4096,
        .block_count = 128,
        .cache_size = 16,
        .lookahead_size = 16,
        .block_cycles = 500,
    };
    /* Wait until other tasks finish screen operations */
    bsp_display_lock(0);
    lv_obj_t *screen = lv_disp_get_scr_act(display);
    lv_obj_set_style_bg_color(screen, lv_color_make(255, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    /* Create a label */
    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "Hello");

    /* Set text color to white */
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);

    /* Center the label */
    lv_obj_center(label);

    /* Load the screen */
    lv_scr_load(screen);
    bsp_display_unlock();

    ESP_LOGI(TAG, "Initialized successfully.");
    return ESP_OK;
}
