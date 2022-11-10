//
// Created by god on 10.11.2022.
//

#ifndef PICO_ST7735_BALL_H
#define PICO_ST7735_BALL_H

#include "engine/Circle.h"
#include "engine/Display.h"
#include "Layers.h"

class Ball : public Circle {
private:
    uint16_t _color = 0x0;
public:
    Ball(double x, double y, double radius, uint16_t color) {
        this->_x = x;
        this->_y = y;
        this->_radius = radius;
        this->_color = color;
        this->set_layer(WALL_LAYER);
    }

    void on_frame_update() override {
        Display::get()->draw_circle(this->_x, this->_y,
                                    this->_radius, this->_color);
    }
    void on_start_intersect(Collidable* collidable) override {
        this->_color = 0xff00;
    }
    void on_stop_intersect(Collidable* collidable) override {
        this->_color = 0x0;
    }
};


#endif //PICO_ST7735_BALL_H
