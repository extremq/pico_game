//
// Created by god on 09.11.2022.
//

#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Collidable.h"

class Circle : public Collidable {
protected:
    double _radius;
public:
    Circle() {
        this->_shape = CIRCLE;
    }

    Circle(double x, double y, double radius) {
        this->_x = x;
        this->_y = y;
        this->_radius = radius;
    }

    bool solve_collision(Collidable* collider) override;

    double get_radius();
    void set_radius(double radius);

};


#endif //_CIRCLE_H
