//
// Created by god on 07.11.2022.
//

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
