//
// Created by god on 06.11.2022.
//

#ifndef _COLLISION_H
#define _COLLISION_H

#include <utility>
#include <cstdint>
#include <vector>

struct Rect {
    uint64_t id;
    double x, y;
    uint16_t h, w;
};

// Class for collision-based computing
// Mostly Rect on Rect collisions
class Collision {
private:
    static Collision* _instance;
    uint64_t _id_cnt = 0; // Used for assigning a unique id to collidables
    Collision() = default;
    std::vector<Rect> _collidable_list;
public:
    static Collision* get() {
        if (_instance == nullptr) {
            _instance = new Collision;
        }
        return _instance;
    }

    // Adds the collidable in struct and assigns it an id
    // Returns the id
    uint64_t add_collidable(double x, double y, uint16_t h, uint16_t w) {
        Rect rect = { this->_id_cnt, x, y, h, w};
        this->_collidable_list.push_back(rect);

        return this->_id_cnt++;
    }

    // Removes a collidable given an id
    void remove_collidable(uint64_t id) {
        for(auto it = this->_collidable_list.begin(); it != this->_collidable_list.end(); ++it)
            if ((*it).id == id)  {
                this->_collidable_list.erase(it);
                return;
            }
    }

    // Returns whether there is an intersection between the two rects
    bool is_colliding_rect_rect(double x0, double y0, uint16_t h0, uint16_t w0,
                                double x1, double y1, uint16_t h1, uint16_t w1);

    // I choose to represent positions using a double, double pair.
    // However, width and height will be an unsigned int.
    // I do not support rotations so there won't be any sub-pixel problems
    std::pair<double, double> solve_collision_rect_rect(double x0, double y0, uint16_t h0, uint16_t w0,
                                                        double x1, double y1, uint16_t h1, uint16_t w1);

    // Check collisions against all collidables
    // Also enables a maximal radius check to skip far away colliders
    std::pair<double, double> solve_all_collisions(double x, double y, uint16_t h, uint16_t w,
                                                   double max_radius_check);
};


#endif //_COLLISION_H
