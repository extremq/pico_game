//
// Created by god on 08.11.2022.
//

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "Collidable.h"

class Rectangle : public Collidable {
protected:
    double _width, _height;
public:
    Rectangle() {
        this->_shape = RECTANGLE;
    };

    Rectangle(double x, double y, double width, double height) {
        this->_x = x;
        this->_y = y;
        this->_height = height;
        this->_width = width;
        this->_shape = RECTANGLE;
    }

    bool solve_collision(Collidable* collider) override;

    double get_height();
    double get_width();
    void set_height(double h);
    void set_width(double w);

};


#endif //_RECTANGLE_H
