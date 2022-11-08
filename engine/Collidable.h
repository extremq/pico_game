//
// Created by god on 07.11.2022.
//

#ifndef _COLLIDABLE_H
#define _COLLIDABLE_H

#include "Drawable.h"

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
protected:
    double _x, _y;
    ShapeOfCollidable _shape;
public:
    // Function to be called when intersected by another object
    // This will be called when other objects call collision function checks
    virtual void on_intersect(Collidable* collidable) {}

    // This function is used for solving a collision
    // based on subtype of collidable
    // Ex -> a circle should use special functions, different from rect
    virtual void solve_collision(Collidable* collidable) {}

    TypeOfCollidable get_type();
    // This should be public for dynamic purposing of a collidable
    void set_type(TypeOfCollidable type);

    // Only getter, can't change shape
    ShapeOfCollidable get_shape();

    uint64_t get_collision_id();
    void set_collision_id(uint64_t id);

    // X and Y appear everywhere
    // They are also passed as protected
    // Because of efficiency
    void set_x(double x);
    double get_x();

    void set_xy(double x, double y);

    void set_y(double y);
    double get_y();
};


#endif //_COLLIDABLE_H
