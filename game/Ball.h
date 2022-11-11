//
// Created by god on 11.11.2022.
//

#ifndef PICO_ST7735_BALL_H
#define PICO_ST7735_BALL_H

#include "engine/Circle.h"
#include "engine/Display.h"

class Ball : public Circle {
    void on_register() override {
        this->set_layer(1);
    }
    void on_frame_update() override {
        Display::get()->fill_circle(pos.x, pos.y, 5, 0xDC5B);
    }
};

#endif //PICO_ST7735_BALL_H
