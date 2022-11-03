#include <iostream>

#include "pico/stdlib.h"
#include "GameEngine.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

uint16_t sprite[4] = {0xffff, 0xffff, 0xffff, 0xffff};

int main() {
    stdio_init_all();

    GameEngine::get()->init(HEIGHT, WIDTH, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES, 0, 26, 27);

    uint8_t xx = 0;
    while(1) {
        uint64_t start_frame = time_us_64();

        uint32_t x = Joystick::get()->x();
        uint32_t y = Joystick::get()->y();
        uint32_t max = Joystick::get()->max_value;

        Display::get()->fill_rect(0, 0, WIDTH, HEIGHT, 0x0);
        Display::get()->fill_rect(x * 127 / max, y * 127 / max, 3, 3, 0x1512);
        Display::get()->fill_rect(69, 69, 4, 20, 0x1512);
        Display::get()->draw_sprite(100, 100, 2, 2, sprite);
        ++xx;
        if (xx == 50)
            xx = 0;
        Display::get()->fill_rect(xx, 0, 4, 20, 0x1512);

        Display::get()->load_frame();
        uint64_t diff = time_us_64() - start_frame;
        sleep_us(16000 - diff);
    }
}
