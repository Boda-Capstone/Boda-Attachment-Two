#Attachment Library
add_library( Attachment
    Attachment.h
    Attachment.c
    )

target_link_libraries(Attachment
    pico_stdlib
    hardware_spi
)
target_include_directories(Attachment PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#SSD1306 Library
add_library( SSD1306
    SSD1306.h
    SSD1306.c
)

target_link_libraries( SSD1306
    pico_stdlib
    hardware_i2c
)

target_include_directories(SSD1306 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")