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
#include "engine/Collision.h"
#include "game/Layers.h"
#include "game/Sprites.h"
#include "Wall.h"
#include "Layers.h"

class testPlayer : public Drawable {
private:
    double _x, _y;
    uint16_t _w, _h;
    double _last_inst_time;
    Joystick* joystick = Joystick::get();
    Display* display = Display::get();
    Time* time = Time::get();
    GameEngine* engine = GameEngine::get();
    Collision* collision = Collision::get();
    Sprite sprite;
public:
    void on_register() override {
        this->_last_inst_time = 0.0;

        this->_w = display->get_width();
        this->_h = display->get_height();
        this->_x = this->_w / 2;
        this->_y = this->_h / 2;

        this->sprite.set_buffer(4, 4, test_sprite);
        this->set_layer(PLAYER_LAYER);
    }

    void on_frame_update() override {
        int8_t x_direction = joystick->get_x_direction();
        int8_t y_direction = joystick->get_y_direction();

        double new_x, new_y; // New coordinates
        new_x = this->_x + x_direction * 40 * time->get_delta_time();
        if (new_x >= this->_w) new_x = this->_w - 1;
        if (new_x < 0) new_x = 0;
        new_y = this->_y + y_direction * 40 * time->get_delta_time();
        if (new_y >= this->_h) new_y = this->_h - 1;
        if (new_y < 0) new_y = 0;

//        std::cout << _x << ' ' << _y << ',' << new_x << ' ' << new_y << '.' << '\n';
//        std::cout << collision->is_colliding_rect_rect(new_x, new_y, this->sprite.get_height(), this->sprite.get_width(),
//                                                       20, 20, 6, 6) << '\n';
        std::pair<double, double> pos =
                collision->solve_collision_rect_rect(new_x, new_y, this->sprite.get_height(), this->sprite.get_width(),
                                                     20, 20, 20, 20);

        pos = collision->solve_collision_rect_rect(pos.first, pos.second, this->sprite.get_height(), this->sprite.get_width(),
                                                   20, 25, 7, 60);

        this->_x = pos.first;
        this->_y = pos.second;

        display->draw_sprite((uint16_t) this->_x, (uint16_t) this->_y,
                             this->sprite.get_height(), this->sprite.get_width(), this->sprite.get_buffer());
    }
};


#endif //PICO_ST7735_TESTPLAYER_H
