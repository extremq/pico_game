//
// Created by god on 05.11.2022.
//

#ifndef _WALL_H
#define _WALL_H

#include <iostream>
#include "engine/Rectangle.h"
#include "engine/Display.h"
#include "Layers.h"

class Wall : public Rectangle {
private:
    uint16_t _color = 0x0;

    Display* display = Display::get();
public:
    Wall(double x, double y, double h, double w, double color) {
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
                           (uint16_t) this->get_height(),(uint16_t) this->get_width(), this->_color);
    }

    void on_start_intersect(Collidable* collidable) override {
        this->_color = 0xff00;
    }
    void on_stop_intersect(Collidable* collidable) override {
        this->_color = 0x0;
    }
};


#endif //_WALL_H
