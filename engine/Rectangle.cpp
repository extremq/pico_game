//
// Created by god on 08.11.2022.
//

#include "Rectangle.h"
#include "CollisionCalculator.h"

bool Rectangle::solve_collision(Collidable *collider) {
    // Check shape and solve
    switch (collider->get_shape()) {
        case RECTANGLE:
            return CollisionCalculator::solve_collision_rect_rect(*this, *(Rectangle*) collider);
        case CIRCLE:
            break;
    }
    return false;
}