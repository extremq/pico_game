//
// Created by god on 07.11.2022.
//

#include <set>
#include <iostream>
#include "Collidable.h"

TypeOfCollidable Collidable::get_type() {
    return this->_type;
}

void Collidable::set_type(TypeOfCollidable type) {
    this->_type = type;
}

ShapeOfCollidable Collidable::get_shape() {
    return this->_shape;
}

uint64_t Collidable::get_collision_id() {
    return this->_collision_id;
}

void Collidable::set_collision_id(uint64_t id) {
    this->_collision_id = id;
}

void Collidable::set_x(double x) {
    this->_x = x;
}

double Collidable::get_x(){
    return this->_x;
}

void Collidable::set_y(double y) {
    this->_y = y;
}

double Collidable::get_y() {
    return this->_y;
}

void Collidable::set_xy(double x, double y) {
    this->_x = x;
    this->_y = y;
}

void Collidable::add_collider_to_list(Collidable *collidable) {
    // Logarithmic time complexity
    this->_colliders.insert({
        collidable->get_collision_id(),
        collidable
    });
}

void Collidable::remove_collider_from_list_and_notify(uint64_t id) {
    // Logarithmic time complexity, again
    // Notify my main collidable that i removed this
    this->on_stop_intersect(this->_colliders.find(id)->second);
    this->_colliders.erase(id);
}

bool Collidable::check_for_collider_in_list(Collidable *collidable) {
    return this->_colliders.find(collidable->get_collision_id()) !=
            this->_colliders.end();
}

// Only need to add, removing is done in bulk by the manager using
// solve_collider_list
void Collidable::add_collider_to_queue(Collidable *collidable) {
    this->_current_colliders.push_back(collidable);
}

void Collidable::erase_colliders() {
    // Erase all colliders. Useful when removing a collidable from the manager
    this->_colliders.clear();
    this->_current_colliders.clear();
}

void Collidable::solve_collider_list() {
    // All around complexity O(3 * nlogn)

    std::set<uint64_t> all_ids;
    for (auto it : this->_colliders) {
        // Copy the collider ids: O(nlogn)
        all_ids.insert(it.first);
    }

    // Treat like a queue and empty out
    while (!this->_current_colliders.empty()) {
        Collidable* collidable = this->_current_colliders.front();
        this->_current_colliders.pop_front();

        // Erase from the ids
        // O(nlogn)
        all_ids.erase(collidable->get_collision_id());

        // Check if it exists inside my previous colliders
        if (!this->check_for_collider_in_list(collidable)) {
            // If it wasn't before, add it
            this->add_collider_to_list(collidable);
            // But also notify the main collidable
            this->on_start_intersect(collidable);
        }
    }

    // Now, we've added all new colliders
    // Remove the ones left
    for(auto it : all_ids) {
        // We already know it has it
        this->remove_collider_from_list_and_notify(it);
    }

    all_ids.clear();
}
