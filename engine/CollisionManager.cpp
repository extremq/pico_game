//
// Created by god on 06.11.2022.
//

#include <iostream>
#include "CollisionManager.h"

CollisionManager* CollisionManager::_instance = nullptr;

void CollisionManager::solve_all_collisions(Collidable* collidable, float max_radius_check=0.0) {
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
                // Reset its colliders
                (*it)->erase_colliders();
                this->_collidable_list.erase(it);
                break;
            }
        this->_collidables_to_be_discarded.pop();
    }

    for (auto _collidable : this->_collidable_list) {
        // TODO use max_radius_check
        // Solves collision for collidable going through all collidables
        // Don't check yourself
        if (_collidable->get_collision_id() != collidable->get_collision_id()) {
            if (collidable->solve_collision(_collidable)) {
                // If collided, update the collidables' queues
                collidable->add_collider_to_queue(_collidable);
                _collidable->add_collider_to_queue(collidable);
            }
        }

        // Solve the other collider's list
        _collidable->solve_collider_list();

    }
    collidable->solve_collider_list();
}
