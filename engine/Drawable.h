//
// Created by god on 03.11.2022.
//

#ifndef PICO_ST7735_DRAWABLE_H
#define PICO_ST7735_DRAWABLE_H

#include "Event.h"
#include "Vector.h"

// Only enforce having a layer. The user can make any kind
// of sprite, sprite array or whatever. The layer matters.
// Layer 0 means first to be drawn.
class Drawable : public Event {
private:
    uint16_t _layer = 0;
public:
    Vector pos;
    void set_layer(uint16_t layer);
    uint16_t get_layer() const;
};


#endif //PICO_ST7735_DRAWABLE_H
