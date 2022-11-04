//
// Created by god on 03.11.2022.
//

#ifndef _SPRITE_H
#define _SPRITE_H

#include <cstdint>

class Sprite {
private:
    // A matrix of 16-bit pixels
    uint16_t* _sprite_buffer = nullptr;
    uint16_t _width = 0;
    uint16_t _height = 0;

public:
    uint16_t *get_buffer();
    uint16_t get_width();
    uint16_t get_height();
    void set_buffer(uint16_t h, uint16_t w, uint16_t* sprite_buffer);
};


#endif //_SPRITE_H
