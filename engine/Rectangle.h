//
// Created by god on 08.11.2022.
//

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "Collidable.h"

class Rectangle : public Collidable {
public:
    float w = 0, h = 0;
    Rectangle() {
        this->_shape = RECTANGLE;
    };

    Rectangle(float x, float y, float width, float height) {
        this->pos.x = x;
        this->pos.y = y;
        this->w = height;
        this->h = width;
        this->_shape = RECTANGLE;
    }

    bool solve_collision(Collidable* collider) override;

};


#endif //_RECTANGLE_H
