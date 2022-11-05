//
// Created by god on 04.11.2022.
//

#ifndef PICO_ST7735_TESTPLAYER_H
#define PICO_ST7735_TESTPLAYER_H

#include "Drawable.h"
#include "Joystick.h"
#include "Display.h"
#include "Sprite.h"
#include "Time.h"
#include <iostream>

extern uint16_t test_sprite[4];

class testPlayer : public Drawable {
private:
    double _x, _y;
    uint16_t _w, _h;
    Joystick* joystick = Joystick::get();
    Display* display = Display::get();
    Time* time = Time::get();
    Sprite sprite;
public:
    testPlayer() {
        this->_w = display->get_width();
        this->_h = display->get_height();
        this->_x = this->_w / 2;
        this->_y = this->_h / 2;

        this->sprite.set_buffer(2, 2, test_sprite);
        this->set_layer(2);
    }

    void on_frame_update() override {
        int8_t x_direction = joystick->get_x_direction();
        int8_t y_direction = joystick->get_y_direction();

        this->_x += x_direction * 40 * time->get_delta_physics_time();
        if (_x >= this->_w) _x = this->_w - 1;
        if (_x < 0) _x = 0;
        this->_y += y_direction * 40 * time->get_delta_physics_time();
        if (_y >= this->_h) _y = this->_h - 1;
        if (_y < 0) _y = 0;

        display->draw_sprite((uint16_t) this->_x, (uint16_t) this->_y,
                             this->sprite.get_height(), this->sprite.get_width(), this->sprite.get_buffer());
    }
};


#endif //PICO_ST7735_TESTPLAYER_H
