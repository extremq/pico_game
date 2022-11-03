//
// Created by god on 03.11.2022.
//

#include "Drawable.h"

void Drawable::set_layer(uint16_t layer) {
    this->_layer = layer;
}

uint16_t Drawable::get_layer(uint16_t layer) {
    return this->_layer;
}
