//
// Created by god on 06.11.2022.
//

#ifndef _COLLISION_H
#define _COLLISION_H

#include <utility>
#include <cstdint>
#include <vector>
#include "Collidable.h"

// Class for collision-based computing
// Only supports Rect on Rect collisions.
// Collision are lazily-checked by the user
class Collision {
private:
    static Collision* _instance;
    uint64_t _id_cnt = 1; // Used for assigning a unique id to collidables
    Collision() = default;
    std::vector<Collidable*> _collidable_list;
public:
    static Collision* get() {
        if (_instance == nullptr) {
            _instance = new Collision;
        }
        return _instance;
    }

    // Adds the collidable in struct and assigns it an id
    void register_collidable(Collidable* c) {
        c->set_collision_id(this->_id_cnt++);
        this->_collidable_list.push_back(c);
    }

    // Removes a collidable given an id
    void discard_collidable(Collidable* c) {
        uint64_t id = c->get_collision_id();
        for(auto it = this->_collidable_list.begin(); it != this->_collidable_list.end(); ++it)
            if ((*it)->get_collision_id() == id)  {
                this->_collidable_list.erase(it);
                return;
            }
    }

    // Returns whether there is an intersection between the two rects
    bool is_intersecting_rect_rect(Collidable* rect1,
                                   Collidable* rect2);

    // I choose to represent positions using a double, double pair.
    // However, width and height will be an unsigned int.
    // I do not support rotations so there won't be any sub-pixel problems
    void solve_collision_rect_rect(Collidable* rect1,
                                   Collidable* rect2);

    // Check collisions against all collidables
    // Also enables a maximal radius check to skip far away colliders
    void solve_all_collisions(Collidable* rect,
                              double max_radius_check);
};


#endif //_COLLISION_H
