//
// Created by god on 09.11.2022.
//

#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Collidable.h"

class Circle : public Collidable {
public:
    float radius = 0;
    Circle() {
        this->_shape = CIRCLE;
    }

    Circle(float x, float y, float radius) {
        this->pos.x = x;
        this->pos.y = y;
        this->radius = radius;
        this->_shape = CIRCLE;
    }

    bool solve_collision(Collidable* collider) override;
};


#endif //_CIRCLE_H
