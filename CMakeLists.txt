cmake_minimum_required(VERSION 3.22.1)
include(pico_sdk_import.cmake)
project(pico_st7735 C CXX ASM)

set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PROJ_NAME shobi)

pico_sdk_init()
add_executable(${PROJ_NAME}
        main.cpp
        engine/Display.cpp
        engine/Display.h
        engine/Frame.cpp
        engine/Frame.h
        engine/GameEngine.cpp
        engine/GameEngine.h
        engine/Event.cpp
        engine/Event.h
        engine/Drawable.cpp
        engine/Drawable.h
        engine/Display.cpp
        engine/Display.h
        engine/Joystick.cpp
        engine/Joystick.h
        engine/ST7735_defines.h
        engine/Sprite.cpp
        engine/Sprite.h
        engine/Time.cpp
        engine/Time.h
        engine/CollisionManager.cpp
        engine/CollisionManager.h
        engine/Collidable.cpp
        engine/Collidable.h
        engine/Rectangle.cpp
        engine/Rectangle.h
        engine/CollisionCalculator.h
        engine/Invokable.h
        engine/Circle.cpp
        engine/Circle.h
        engine/Vector.h
        game/test.cpp game/test.h game/Ball.h)

pico_enable_stdio_usb(${PROJ_NAME} 1)
pico_enable_stdio_uart(${PROJ_NAME} 0)
pico_add_extra_outputs(${PROJ_NAME})

target_include_directories(${PROJ_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(${PROJ_NAME}
        hardware_spi
        hardware_adc
        pico_stdlib
        )

# Remove this when you compile
add_custom_command(TARGET
        ${PROJ_NAME} POST_BUILD
        COMMAND
        sudo -S /bin/sh ${PROJECT_SOURCE_DIR}/deploy.sh ${PROJECT_SOURCE_DIR}/build/${PROJ_NAME}.uf2
        )