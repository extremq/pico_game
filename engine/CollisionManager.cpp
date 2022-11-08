//
// Created by god on 06.11.2022.
//

#include <iostream>
#include "CollisionManager.h"

CollisionManager* CollisionManager::_instance = nullptr;

void CollisionManager::solve_all_collisions(Collidable* rect, double max_radius_check) {
    for (auto _rect : this->_collidable_list) {
        // TODO use max_radius_check
        // Solves collision for rect going through all collidables
        // Don't check yourself
        if (_rect->get_collision_id() != rect->get_collision_id())
            rect->solve_collision(_rect);
    }
}
