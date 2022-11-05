//
// Created by god on 05.11.2022.
//

#ifndef _WALL_H
#define _WALL_H

#include "engine/Drawable.h"
#include "engine/Display.h"

class Wall : public Drawable {
private:
    uint16_t bg_color = 0x0;

    Display* display = Display::get();
public:
    Wall() {
        this->set_layer(2);
    }
    void on_frame_update() override {
        display->fill_rect(5, 5, 10,
                           10, this->bg_color);
    }
};


#endif //_WALL_H
