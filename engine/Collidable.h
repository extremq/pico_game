//
// Created by god on 07.11.2022.
//

#ifndef _COLLIDABLE_H
#define _COLLIDABLE_H

#include "Drawable.h"

// This object has rect describers and a layer
// This engine only supports rectangle collisions
// Extend it if you'd like!
class Collidable : public Drawable {
private:
    uint64_t _collision_id;
    double _x, _y;
    uint16_t _h, _w;
public:
    uint64_t get_collision_id() {
        return this->_collision_id;
    }

    void set_collision_id(uint64_t id) {
        this->_collision_id = id;
    }

    void set_x(double x) {
        this->_x = x;
    }

    double get_x() {
        return this->_x;
    }

    void set_y(double y) {
        this->_y = y;
    }

    double get_y() {
        return this->_y;
    }


    void set_height(uint16_t h) {
        this->_h = h;
    }

    uint16_t get_height() {
        return this->_h;
    }

    void set_width(uint16_t w) {
        this->_w = w;
    }

    uint16_t get_width() {
        return this->_w;
    }
};


#endif //_COLLIDABLE_H
