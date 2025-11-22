file(GLOB_RECURSE UI_SOURCES
    "src/*.c"
)

idf_component_register(
    SRCS ${UI_SOURCES}
    INCLUDE_DIRS "src"
    REQUIRES lvgl
)