//
// Created by god on 08.11.2022.
//

#include <iostream>
#include "Rectangle.h"
#include "CollisionCalculator.h"

bool Rectangle::solve_collision(Collidable *collider) {
    // Check shape and solve
    switch (collider->get_shape()) {
        case RECTANGLE:
            return CollisionCalculator::solve_collision_rect_rect(this, (Rectangle*) collider);
        case CIRCLE:
            break;
    }
    return false;
}

double Rectangle::get_height() {
    return this->_height;
}

double Rectangle::get_width() {
    return this->_width;
}

void Rectangle::set_height(double h) {
    this->_height = h;
}

void Rectangle::set_width(double w) {
    this->_width = w;
}
