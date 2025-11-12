idf_component_register(SRCS "main.c"
                       PRIV_REQUIRES spi_flash
                       INCLUDE_DIRS ""
                       REQUIRES app_manager esp_littlefs lvgl__lvgl)
littlefs_create_partition_image(littlefs ../flash_data FLASH_IN_PROJECT)
                       
