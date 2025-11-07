idf_component_register(
    SRCS "app_manager.c" "img_bulb_gif.c"
    INCLUDE_DIRS "."
    REQUIRES esp_common esp_timer lvgl__lvgl espressif__esp_lvgl_port esp32_c3_lcdkit txp666__otto-emoji-gif-component animated_gif)