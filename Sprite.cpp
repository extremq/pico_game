//
// Created by god on 03.11.2022.
//

#include "Sprite.h"

uint16_t *Sprite::get_sprite_buffer() {
    return _sprite_buffer;
}

uint16_t Sprite::get_width() {
    return _width;
}

uint16_t Sprite::get_height() {
    return _height;
}

void Sprite::set_sprite_buffer(uint16_t h, uint16_t w, uint16_t *sprite_buffer) {
    this->_sprite_buffer = sprite_buffer;
    this->_height = h;
    this->_width = w;
}
