//
// Created by god on 06.11.2022.
//

#ifndef _COLLISION_H
#define _COLLISION_H

#include <utility>
#include <cstdint>
#include <list>
#include <queue>
#include "Collidable.h"

// Class for collision-based computing
// CollisionManager are lazily-checked by the user
// using SolveAllCollisions on a Collidable
class CollisionManager {
private:
    static CollisionManager* _instance;
    uint64_t _id_cnt = 1; // Used for assigning a unique id to collidables
    CollisionManager() = default;

    // Same deal with GameEngine.h and its events system
    // We cannot guarantee that a collidable doesn't remove other
    // collidables in the on_intersect function.
    std::queue<Collidable*> _collidables_to_be_added;
    std::queue<Collidable*> _collidables_to_be_discarded;
    std::list<Collidable*> _collidable_list;
public:
    static CollisionManager* get() {
        if (_instance == nullptr) {
            _instance = new CollisionManager;
        }
        return _instance;
    }

    // Adds the collidable in struct and assigns it an id
    void register_collidable(Collidable* c) {
        this->_collidables_to_be_added.push(c);
    }

    // Removes a collidable given an id
    void discard_collidable(Collidable* c) {
        this->_collidables_to_be_discarded.push(c);
    }

    // Check collisions against all collidables
    // Also enables a maximal radius check to skip far away colliders
    void solve_all_collisions(Collidable* rect,
                              double max_radius_check);
};


#endif //_COLLISION_H
