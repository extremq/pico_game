//
// Created by god on 09.11.2022.
//

#include "Circle.h"
#include "CollisionCalculator.h"

bool Circle::solve_collision(Collidable *collider) {
    // Check shape and solve
    switch (collider->get_shape()) {
        case RECTANGLE:
            return CollisionCalculator::solve_collision_circle_rect(*this, *(Rectangle*) collider);
        case CIRCLE:
            return CollisionCalculator::solve_collision_circle_circle(*this, *(Circle*) collider);
    }
    return false;
}
