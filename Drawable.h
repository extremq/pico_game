//
// Created by god on 03.11.2022.
//

#ifndef PICO_ST7735_DRAWABLE_H
#define PICO_ST7735_DRAWABLE_H

#include "Event.h"
#include "Sprite.h"

class Drawable : public Event {
private:
    uint16_t _layer = 0;
public:
    Sprite sprite;
    void set_layer(uint16_t layer);
    uint16_t get_layer(uint16_t layer);
};


#endif //PICO_ST7735_DRAWABLE_H
