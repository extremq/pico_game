//
// Created by god on 05.11.2022.
//

#ifndef _WALL_H
#define _WALL_H

#include "engine/Drawable.h"
#include "engine/Display.h"
#include "Layers.h"

class Wall : public Drawable {
private:
    uint16_t _bg_color = 0x0;
    uint16_t _x = 0, _y = 0;

    Display* display = Display::get();
public:
    uint16_t w, h;
    void set_color(uint16_t color) {
        this->_bg_color = color;
    }

    void set_x(uint16_t x) {
        this->_x = x;
    }

    void set_y(uint16_t y) {
        this->_y = y;
    }

    void on_register() override {
        this->set_layer(WALL_LAYER);
    }

    void on_frame_update() override {
        display->fill_rect(this->_x, this->_y, h,
                           w, this->_bg_color);
    }
};


#endif //_WALL_H
