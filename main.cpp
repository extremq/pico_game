#include <iostream>

#include "pico/stdlib.h"
#include "GameEngine.h"
#include "testPlayer.h"
#include "Background.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

int main() {
    stdio_init_all();
    sleep_ms(500);

    GameEngine::get()->init(HEIGHT, WIDTH, TFT_CS, TFT_DC,
                            TFT_SDA, TFT_SCL, TFT_RES, 0, 26, 27);
    testPlayer player;
    Background background;
    GameEngine::get()->register_drawable(&player);
    GameEngine::get()->register_drawable(&background);
    GameEngine::get()->start_game();
}
