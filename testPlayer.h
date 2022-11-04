//
// Created by god on 04.11.2022.
//

#ifndef PICO_ST7735_TESTPLAYER_H
#define PICO_ST7735_TESTPLAYER_H

#include "Drawable.h"
#include "Joystick.h"
#include "Display.h"
#include "Sprite.h"
#include <iostream>

extern uint16_t test_sprite[4];

class testPlayer : public Drawable {
private:
    uint16_t _x, _y;
    Joystick* joystick = Joystick::get();
    Display* display = Display::get();
    Sprite sprite;
public:
    testPlayer() {
        this->_x = 0;
        this->_y = 0;
        this->sprite.set_buffer(2, 2, test_sprite);
        this->set_layer(0);
    }

    void on_frame_update() override {
        uint32_t x = joystick->get_x();
        uint32_t y = joystick->get_y();
        uint32_t max_value = joystick->get_max_value();
        display->draw_sprite(x * 128 / max_value, y * 128 / max_value,
                             this->sprite.get_height(), this->sprite.get_width(), this->sprite.get_buffer());
    }
};


#endif //PICO_ST7735_TESTPLAYER_H
