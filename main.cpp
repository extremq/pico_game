#include <iostream>

#include "pico/stdlib.h"
#include "engine/GameEngine.h"
#include "game/testPlayer.h"
#include "game/Background.h"
#include "game/Wall.h"

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

    Wall* wall = new Wall;
    wall->set_x(20);
    wall->set_y(20);
    wall->h = 20;
    wall->w = 20;
    Wall* wall2 = new Wall;
    wall2->set_x(20);
    wall2->set_y(25);
    wall2->h = 7;
    wall2->w = 60;
    testPlayer* player = new testPlayer;
    Background* background = new Background;
    GameEngine::get()->register_drawable(wall);
    GameEngine::get()->register_drawable(wall2);
    GameEngine::get()->register_drawable(player);
    GameEngine::get()->register_drawable(background);
    GameEngine::get()->start_engine();
}
