//
// Created by god on 06.11.2022.
//

#ifndef _COLLISION_H
#define _COLLISION_H

#include <utility>
#include <cstdint>

// Class for collision-based computing
// Mostly rect on rect collisions
class Collision {
private:
    static Collision* _instance;
public:
    static Collision* get() {
        if (_instance == nullptr) {
            _instance = new Collision;
        }
        return _instance;
    }

    // Returns whether there is an intersection between the two rects
    bool is_colliding_rect_rect(double x0, double y0, uint16_t h0, uint16_t w0,
                                double x1, double y1, uint16_t h1, uint16_t w1);

    // I choose to represent positions using a double, double pair.
    // However, width and height will be an unsigned int.
    // I do not support rotations so there won't be any sub-pixel problems
    std::pair<double, double> solve_collision_rect_rect(double x0, double y0, uint16_t h0, uint16_t w0,
                                                        double x1, double y1, uint16_t h1, uint16_t w1);

};


#endif //_COLLISION_H
