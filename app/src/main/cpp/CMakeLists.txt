cmake_minimum_required(VERSION 3.22.1)

project("kafka")

add_library(${CMAKE_PROJECT_NAME} SHARED
        kafka.cpp
        base64.cpp
        utilities.cpp
        )

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        )

# Add compile options to your target
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -fvisibility=hidden
        -fvisibility-inlines-hidden
        -ffunction-sections -fdata-sections
        -Wl,--gc-sections
        )
