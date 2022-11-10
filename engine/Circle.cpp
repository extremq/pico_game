//
// Created by god on 09.11.2022.
//

#include "Circle.h"
#include "CollisionCalculator.h"

bool Circle::solve_collision(Collidable *collider) {
    // Check shape and solve
    switch (collider->get_shape()) {
        case RECTANGLE:
            break;
        case CIRCLE:
            return CollisionCalculator::solve_collision_circle_circle(this, (Circle*) collider);
    }
    return false;
}

double Circle::get_radius() {
    return this->_radius;
}

void Circle::set_radius(double radius) {
    this->_radius = radius;
}
