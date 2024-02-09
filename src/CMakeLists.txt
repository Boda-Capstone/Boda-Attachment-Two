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
