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
    uint16_t _color = 0x0;
    uint16_t _x = 0, _y = 0;
    uint16_t _w = 16, _h = 16;

    Display* display = Display::get();
public:
    void set_config(uint16_t x, uint16_t y, uint16_t h, uint16_t w, uint16_t color) {
        this->_x = x;
        this->_y = y;
        this->_h = h;
        this->_w = w;
        this->_color = color;
    }

    void set_color(uint16_t color) {
        this->_color = color;
    }

    void set_x(uint16_t x) {
        this->_x = x;
    }

    void set_y(uint16_t y) {
        this->_y = y;
    }

    void set_h(uint16_t h) {
        this->_h = h;
    }

    void set_w(uint16_t w) {
        this->_w = w;
    }

    void on_register() override {
        this->set_layer(WALL_LAYER);
    }

    void on_frame_update() override {
        display->draw_rect(this->_x, this->_y, this->_h,
                           this->_w, this->_color);
    }
};


#endif //_WALL_H
