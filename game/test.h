//
// Created by god on 11.11.2022.
//

#ifndef PICO_ST7735_TEST_H
#define PICO_ST7735_TEST_H


#include "engine/Drawable.h"
#include "engine/Display.h"
#include "engine/Joystick.h"
#include "engine/GameEngine.h"
#include "engine/Time.h"
#include "Ball.h"

class test : Drawable {
public:
    int16_t radius = 0;
    float last_time = 0;
    float last_time_ball = 0;
    Ball* ball = nullptr;
    test() {
        GameEngine::get()->register_drawable(this);
        ball = new Ball;
        ball->pos.x = 40;
        ball->pos.y = 40;
        GameEngine::get()->register_drawable(ball);
    }

    void on_frame_update() override {
        if (Time::get()->get_game_time() - last_time > 0.1)  {
            last_time = Time::get()->get_game_time();
            radius = (radius + 1) % 16;
            Display::get()->fill_rect(0, 0,
                                      Display::get()->get_height(), Display::get()->get_width(),
                                      0x0);
            Display::get()->draw_circle(64, 64, radius, 0xFF8D);
            Display::get()->draw_circle(64, 64, radius - 2, 0xFF2B);
            Display::get()->draw_circle(64, 64, radius - 4, 0xF685);
            Display::get()->draw_circle(64, 64, radius - 6, 0xF602);
        }

        if (Time::get()->get_game_time() - last_time_ball > 5) {
            last_time_ball = Time::get()->get_game_time();
            GameEngine::get()->discard_drawable(ball);
            ball->pos.x = 40 + radius;
            ball->pos.y = 40 + radius;
            GameEngine::get()->register_drawable(ball);
        }
    }
};


#endif //PICO_ST7735_TEST_H
