//
// Created by god on 06.11.2022.
//

#include <iostream>
#include "CollisionManager.h"

CollisionManager* CollisionManager::_instance = nullptr;

void CollisionManager::solve_all_collisions(Collidable* rect, double max_radius_check) {
    // Commit collider changes - analogue to GameEngine.h
    while (!this->_collidables_to_be_added.empty()) {
        Collidable* c = this->_collidables_to_be_added.front();

        // Set id and add to list
        c->set_collision_id(this->_id_cnt++);
        this->_collidable_list.push_back(c);

        this->_collidables_to_be_added.pop();
    }

    while (!this->_collidables_to_be_discarded.empty()) {
        Collidable* c = this->_collidables_to_be_discarded.front();

        // Get id of collider and erase the corresponding element
        // Again, not ideal speed, but hopefully we don't abuse this
        uint64_t id = c->get_collision_id();
        for(auto it = this->_collidable_list.begin(); it != this->_collidable_list.end(); ++it)
            if ((*it)->get_collision_id() == id)  {
                this->_collidable_list.erase(it);
                return;
            }

        this->_collidables_to_be_discarded.pop();
    }

    for (auto _rect : this->_collidable_list) {
        // TODO use max_radius_check
        // Solves collision for rect going through all collidables
        // Don't check yourself
        if (_rect->get_collision_id() != rect->get_collision_id())
            rect->solve_collision(_rect);
    }
}
