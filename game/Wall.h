//
// Created by god on 05.11.2022.
//

#ifndef _WALL_H
#define _WALL_H

#include "engine/Collidable.h"
#include "engine/Display.h"
#include "Layers.h"

class Wall : public Collidable {
private:
    uint16_t _color = 0x0;

    Display* display = Display::get();
public:
    void set_config(uint16_t x, uint16_t y, uint16_t h, uint16_t w, uint16_t color) {
        this->set_x(x);
        this->set_y(y);
        this->set_width(w);
        this->set_height(h);
        this->set_type(COLLISION);
        this->_color = color;
    }

    void set_color(uint16_t color) {
        this->_color = color;
    }

    void on_register() override {
        this->set_layer(WALL_LAYER);
    }

    void on_frame_update() override {
        display->fill_rect((uint16_t) this->get_x(), (uint16_t) this->get_y(),
                           this->get_height(),this->get_width(), this->_color);
    }
};


#endif //_WALL_H
