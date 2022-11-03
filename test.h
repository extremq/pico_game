//
// Created by god on 04.11.2022.
//

#ifndef _TEST_H
#define _TEST_H

#include "Drawable.h"
#include "Joystick.h"
#include "Display.h"

extern uint16_t test_sprite[4];

class test : public Drawable  {
private:
    uint16_t _x, _y;
    Joystick* joystick = Joystick::get();
    Display* display = Display::get();
public:
    test() {
        this->on_init();
    }
    void on_frame_update() override {
        uint32_t x = joystick->get_x();
        uint32_t y = joystick->get_y();
        uint32_t max_value = joystick->get_max_value();
        display->fill_rect(0, 0, display->get_height(), display->get_width(), 0x4444);
        display->draw_sprite(x * 128 / max_value, y * 128 / max_value,
                             this->sprite.get_height(), this->sprite.get_width(), this->sprite.get_sprite_buffer());
    }

    void on_init() {
        this->_x = 0;
        this->_y = 0;
        this->sprite.set_sprite_buffer(2, 2, test_sprite);
        this->set_layer(0);
    }
};


#endif //_TEST_H
