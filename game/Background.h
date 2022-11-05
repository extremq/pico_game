//
// Created by god on 04.11.2022.
//

#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "engine/Drawable.h"
#include "engine/Display.h"

class Background : public Drawable {
private:
    uint16_t bg_color = 0x32EB;
    uint16_t disp_width, disp_height;

    Display* display = Display::get();
public:
    Background() {
        this->set_layer(1);
        this->disp_height = display->get_height();
        this->disp_width = display->get_width();
    }
    void on_frame_update() override {
        display->fill_rect(0, 0, this->disp_height,
                           this->disp_width, this->bg_color);
    }
};


#endif //_BACKGROUND_H
