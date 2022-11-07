//
// Created by god on 06.11.2022.
//

#include <iostream>
#include "Collision.h"

Collision* Collision::_instance = nullptr;

std::pair<double, double>
Collision::solve_collision_rect_rect(double x0, double y0, uint16_t h0, uint16_t w0,
                                     double x1, double y1, uint16_t h1, uint16_t w1) {
    // TODO repair sliding
    // Where should Rect 1 (x0, y0, h0, w0) be placed in order to clamp the intersection?
    std::pair<double, double> pos(x0, y0);

    // Get right corners
    double x0_s = x0 + w0;
    double y0_s = y0 + h0;
    double x1_s = x1 + w1;
    double y1_s = y1 + h1;

    // Rectangles are separated on x
    if (x0 > x1_s || x1 > x0_s) return pos;

    // Rectangles are separated on y
    if (y0_s < y1 || y1_s < y0) return pos;

    // This means we intersected.
    if (x0 < x1) {
        // First rectangle is on the left side
        if (y0 < y1) {
            // First rectangle is on the left side and above second rectangle
            if (x0_s - x1 < y0_s - y1) {
                // If moving the rectangle to the left is less than moving above
                x0 -= x0_s - x1;
            }
            else {
                y0 -= y0_s - y1;
            }
        }
        else if (y0_s <= y1_s) {
            // Between up side and down side
            x0 -= x0_s - x1;
        }
        else {
            // First rectangle is on the left side but below second rectangle
            std::cout << x0_s << ' ' << x1 << ' ' << y1_s << ' ' << y0 << '\n';
            if (x0_s - x1 < y1_s - y0) {
                // If moving the rectangle to the left is less than moving below
                x0 -= x0_s - x1;
            }
            else {
                y0 += y1_s - y0;
            }
        }
    }
    else if (x0_s <= x1_s) {
        // First rectangle is between the sides
        if (y0 < y1) {
            // And above
            y0 -= y0_s - y1;
        }
        else if (y0_s <= y1_s) {
            // Or between (inside completely)
            double min_x, min_y;
            if (x0_s - x1 < x1_s - x0) {
                // If it's better to move the rectangle left than right
                min_x = -(x0_s - x1);
            }
            else {
                min_x = x1_s - x0;
            }

            if (y0_s - y1 < y1_s - y0) {
                // If it's better to move the rectangle above than below
                min_y = -(y0_s - y1);
            }
            else {
                min_y = y1_s - y0;
            }

            if (min_x < min_y) {
                // Move x rather than y
                x0 += min_x;
            }
            else {
                y0 += min_y;
            }
        }
        else {
            // Or below
            y0 += y1_s - y0;
        }
    }
    else {
        // First rectangle is on the right side
        if (y0 < y1) {
            // First rectangle is on the right side and above second rectangle
            if (x1_s - x0 < y0_s - y1) {
                // If moving the rectangle to the right is less than moving above
                x0 += x1_s - x0;
            }
            else {
                y0 -= y0_s - y1;
            }
        }
        else if (y0_s < y1_s) {
            // Between up side and down side
            x0 += x1_s - x0;
        }
        else {
            // First rectangle is on the right side but below second rectangle
            if (x1_s - x0 <= y1_s - y0) {
                // If moving the rectangle to the right is less than moving below
                x0 += x1_s - x0;
            }
            else {
                y0 += y1_s - y0;
            }
        }
    }

    pos.first = x0;
    pos.second = y0;
    return pos;
}

bool
Collision::is_colliding_rect_rect(double x0, double y0, uint16_t h0, uint16_t w0,
                                  double x1, double y1, uint16_t h1, uint16_t w1) {
    if (h0 == 0 || w0 == 0 || h1 == 0 || w1 == 0)
        // Area 0
        return false;

    // Get right corners
    double x0_s = x0 + w0;
    double y0_s = y0 + h0;
    double x1_s = x1 + w1;
    double y1_s = y1 + h1;

    // Rectangles are separated on x
    if (x0 > x1_s || x1 > x0_s) return false;

    // Rectangles are separated on y
    if (y0_s < y1 || y1_s < y0) return false;

    return true;
}

std::pair<double, double>
Collision::solve_all_collisions(double x, double y, uint16_t h, uint16_t w, double max_radius_check) {
    std::pair<double, double> pos(x, y);

    for (auto rect : this->_collidable_list) {
        // TODO use max_radius_check
        pos = this->solve_collision_rect_rect(pos.first, pos.second, h, w,
                                              rect.x, rect.y, rect.h, rect.w);
    }

    return pos;
}
