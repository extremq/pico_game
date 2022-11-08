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
#include "engine/Rectangle.h"
#include "game/Layers.h"
#include "game/Sprites.h"
#include "Wall.h"
#include "Layers.h"

class testPlayer : public Rectangle {
private:
    double _last_inst_time;
    Joystick* joystick = Joystick::get();
    Display* display = Display::get();
    Time* time = Time::get();
    GameEngine* engine = GameEngine::get();
    CollisionManager* collision = CollisionManager::get();
    Sprite sprite;
public:
    void on_register() override {
        this->_last_inst_time = 0.0;

        this->set_x(display->get_width() / 2.0);
        this->set_y(display->get_height() / 2.0);
        this->set_type(COLLISION);

        this->sprite.set_buffer(4, 4, test_sprite);
        this->set_width(sprite.get_width());
        this->set_height(sprite.get_height());
        this->set_layer(PLAYER_LAYER);
    }

    void on_frame_update() override {
        double x = this->get_x(), y = this->get_y();
        double new_x, new_y; // New coordinates
        double h = this->get_height(), w = this->get_width();

        uint16_t screen_h = display->get_height(), screen_w = display->get_width();
        int8_t x_direction = joystick->get_x_direction();
        int8_t y_direction = joystick->get_y_direction();

        new_x = x + x_direction * 60 * time->get_delta_time();
        if (new_x > screen_w - w) new_x = screen_w - w;
        if (new_x < 0) new_x = 0;
        new_y = y + y_direction * 60 * time->get_delta_time();
        if (new_y > screen_h - h) new_y = screen_h - h;
        if (new_y < 0) new_y = 0;

        this->set_xy(new_x, new_y);
        collision->solve_all_collisions(this, 10.0);

        display->draw_sprite((uint16_t) this->get_x(), (uint16_t) this->get_y(),
                             (uint16_t) this->get_height(), (uint16_t) this->get_width(), this->sprite.get_buffer());
    }
};


#endif //PICO_ST7735_TESTPLAYER_H
