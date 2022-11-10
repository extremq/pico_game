//
// Created by god on 07.11.2022.
//

#ifndef _COLLIDABLE_H
#define _COLLIDABLE_H

#include <map>
#include <list>
#include "Drawable.h"
#include "Vector.h"

// Want to have collidables that aren't physical
enum TypeOfCollidable {
    COLLISION, INTERSECTION
};

enum ShapeOfCollidable {
    RECTANGLE, CIRCLE
};

// This object has rect describers and a layer
// This engine only supports rectangle collisions
// Extend it if you'd like!
class Collidable : public Drawable {
private:
    uint64_t _collision_id;
    TypeOfCollidable _type = COLLISION; // default
    std::map<uint64_t, Collidable*> _colliders; // List of intersecting colliders
    std::list<Collidable*> _current_colliders; // Queue of current frame colliders

    // Should be used only by the Collision Manager

    // This function is used for solving a collision
    // based on subtype of collidable
    // Ex -> a circle should use special functions, different from rect
    virtual bool solve_collision(Collidable* collidable) { return false; }

    // _colliders and _current_colliders functions
    void add_collider_to_list(Collidable* collidable);
    void remove_collider_from_list_and_notify(uint64_t id);
    bool check_for_collider_in_list(Collidable* collidable);
    void erase_colliders();
    void add_collider_to_queue(Collidable* collidable);
    void solve_collider_list();
    void set_collision_id(uint64_t id);
protected:
    ShapeOfCollidable _shape;
public:
    Vector pos;
    // Function to be called when intersected by another object
    // This will be called when other objects call collision function checks
    virtual void on_start_intersect(Collidable* collidable) {}

    // Called when the object stops intersecting with collidable
    virtual void on_stop_intersect(Collidable* collidable) {}


    TypeOfCollidable get_type();
    // This should be public for dynamic purposing of a collidable
    void set_type(TypeOfCollidable type);

    // Only getter, can't change shape
    ShapeOfCollidable get_shape();

    uint64_t get_collision_id() const;

    // BFF!
    friend class CollisionManager;
};


#endif //_COLLIDABLE_H
