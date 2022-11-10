//
// Created by god on 04.11.2022.
//

#ifndef PICO_ST7735_TESTPLAYER_H
#define PICO_ST7735_TESTPLAYER_H

#include <iostream>
#include "engine/Drawable.h"
#include "engine/Joystick.h"
#include "engine/Display.h"
#include "engine/Sprite.h"
#include "engine/Time.h"
#include "engine/GameEngine.h"
#include "engine/CollisionManager.h"
#include "engine/Circle.h"
#include "game/Layers.h"
#include "Wall.h"
#include "Layers.h"

class testPlayer : public Circle {
private:
    Joystick* joystick = Joystick::get();
    Display* display = Display::get();
    Time* time = Time::get();
    GameEngine* engine = GameEngine::get();
    CollisionManager* collision = CollisionManager::get();
public:
    void on_register() override {
        this->set_x(display->get_width() / 2.0);
        this->set_y(display->get_height() / 2.0);
        this->set_type(COLLISION);

        this->set_radius(4);
        this->set_layer(PLAYER_LAYER);
    }

    void on_frame_update() override {
        double x = this->get_x(), y = this->get_y();
        double new_x, new_y; // New coordinates
        double r = this->get_radius();

        uint16_t screen_h = display->get_height(), screen_w = display->get_width();
        int8_t x_direction = joystick->get_x_direction();
        int8_t y_direction = joystick->get_y_direction();

        new_x = x + x_direction * 60 * time->get_delta_time();
        if (new_x > screen_w - r) new_x = screen_w - r;
        if (new_x < 0) new_x = 0;
        new_y = y + y_direction * 60 * time->get_delta_time();
        if (new_y > screen_h - r) new_y = screen_h - r;
        if (new_y < 0) new_y = 0;

        this->set_xy(new_x, new_y);
        collision->solve_all_collisions(this, 10.0);

        display->draw_circle(_x, _y, _radius, 0xffff);
    }

    void on_start_intersect(Collidable* collidable) override {
        std::cout << "on\n";
    }
    void on_stop_intersect(Collidable* collidable) override {
        std::cout << "off\n";
    }
};


#endif //PICO_ST7735_TESTPLAYER_H
