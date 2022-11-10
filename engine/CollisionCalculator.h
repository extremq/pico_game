//
// Created by god on 08.11.2022.
//

#ifndef _COLLISIONCALCULATOR_H
#define _COLLISIONCALCULATOR_H

#include "Rectangle.h"
#include "Circle.h"
#include <cmath>
#include <iostream>

/*
 * Header for all collision computations
 */

namespace CollisionCalculator {
    static bool is_intersecting_rect_rect(Rectangle& rect1,
                                          Rectangle& rect2) {
        // Get right corners
        Vector corner1, corner2;
        corner1.x = rect1.pos.x + rect1.w;
        corner1.y = rect1.pos.y + rect1.h;
        corner2.x = rect2.pos.x + rect2.w;
        corner2.y = rect2.pos.y + rect2.h;

        // Rectangles are separated on x
        if (rect1.pos.x > corner2.x || rect2.pos.x > corner1.x) return false;

        // Rectangles are separated on y
        if (corner1.y  < rect2.pos.y || corner2.y < rect1.pos.y) return false;

        return true;
    }

    static float distance(const Vector& a, const Vector& b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    static bool solve_collision_circle_rect(Circle& circle,
                                            Rectangle& rect) {
        // Nearest point on rectangle
        Vector nearest_point;
        nearest_point.x = std::max(rect.pos.x, std::min(circle.pos.x, rect.pos.x + rect.w));
        nearest_point.y = std::max(rect.pos.y, std::min(circle.pos.y, rect.pos.y + rect.h));

        // Ray to nearest point
        Vector ray_to_nearest_point = nearest_point - circle.pos;

        const float mag = ray_to_nearest_point.mag();
        const float overlap = circle.radius - mag;

        if (overlap < -1e-5) return false;

        // Maybe intersection trigger
        if (rect.get_type() != COLLISION)
            return true;

        // Resolution
        circle.pos.x -= ray_to_nearest_point.x / mag * overlap;
        circle.pos.y -= ray_to_nearest_point.y / mag * overlap;

        return true;
    }

    static bool solve_collision_circle_circle(Circle& circle1,
                                              Circle& circle2) {
        float dist = CollisionCalculator::distance(circle1.pos, circle2.pos);

        // TODO Maybe make it stick better?

        // Isn't intersecting
        if (dist > circle1.radius + circle2.radius) return false;

        // get the vector from the center of circle2 that points
        // to center of circle1
        // normalize it and multiply it by the sum of radii
        Vector tg;
        tg.x = (circle2.pos.x - circle1.pos.x) / dist;
        tg.y = (circle2.pos.y - circle1.pos.y) / dist;

        circle1.pos = circle2.pos - tg * (circle1.radius + circle2.radius);

        return true;
    }

    static bool solve_collision_rect_rect(Rectangle& rect1,
                                          Rectangle& rect2) {
        // TODO use vectors and compute ACTUAL result
        // Get right corners
        Vector corner1, corner2;
        corner1.x = rect1.pos.x + rect1.w;
        corner1.y = rect1.pos.y + rect1.h;
        corner2.x = rect2.pos.x + rect2.w;
        corner2.y = rect2.pos.y + rect2.h;

        // Rectangles are separated on x
        if (rect1.pos.x > corner2.x || rect2.pos.x > corner1.x) return false;

        // Rectangles are separated on y
        if (corner1.y  < rect2.pos.y || corner2.y < rect1.pos.y) return false;

        // This means we intersected.

        // Act as an intersection check if the second Rectangle isn't based
        // on physical collision
        if (rect2.get_type() != COLLISION)
            return true;

        if (rect1.pos.x < rect2.pos.x) {
            // First rectangle is on the left side
            if (rect1.pos.y < rect2.pos.y) {
                // First rectangle is on the left side and above second rectangle
                if (corner1.x - rect2.pos.x < corner1.y - rect2.pos.y) {
                    // If moving the rectangle to the left is less than moving above
                    rect1.pos.x -= corner1.x - rect2.pos.x;
                }
                else {
                    rect1.pos.y -= corner1.y - rect2.pos.y;
                }
            }
            else if (corner1.y <= corner2.y) {
                // Between up side and down side
                rect1.pos.x -= corner1.x - rect2.pos.x;
            }
            else {
                // First rectangle is on the left side but below second rectangle
                if (corner1.x - rect2.pos.x < corner2.y - rect1.pos.y) {
                    // If moving the rectangle to the left is less than moving below
                    rect1.pos.x -= corner1.x - rect2.pos.x;
                }
                else {
                    rect1.pos.y += corner2.y - rect1.pos.y;
                }
            }
        }
        else if (corner1.x <= corner2.x) {
            // First rectangle is between the sides
            if (rect1.pos.y < rect2.pos.y) {
                // And above
                rect1.pos.y -= corner1.y - rect2.pos.y;
            }
            else if (corner1.y <= corner2.y) {
                // Or between (inside completely)
                float min_x, min_y;
                if (corner1.x - rect2.pos.x < corner2.x - rect1.pos.x) {
                    // If it's better to move the rectangle left than right
                    min_x = -(corner1.x - rect2.pos.x);
                }
                else {
                    min_x = corner2.x - rect1.pos.x;
                }

                if (corner1.y - rect2.pos.y < corner2.y - rect1.pos.y) {
                    // If it's better to move the rectangle above than below
                    min_y = -(corner1.y - rect2.pos.y);
                }
                else {
                    min_y = corner2.y - rect1.pos.y;
                }

                if (min_x < min_y) {
                    // Move x rather than y
                    rect1.pos.x += min_x;
                }
                else {
                    rect1.pos.y += min_y;
                }
            }
            else {
                // Or below
                rect1.pos.y += corner2.y - rect1.pos.y;
            }
        }
        else {
            // First rectangle is on the right side
            if (rect1.pos.y < rect2.pos.y) {
                // First rectangle is on the right side and above second rectangle
                if (corner2.x - rect1.pos.x < corner1.y - rect2.pos.y) {
                    // If moving the rectangle to the right is less than moving above
                    rect1.pos.x += corner2.x - rect1.pos.x;
                }
                else {
                    rect1.pos.y -= corner1.y - rect2.pos.y;
                }
            }
            else if (corner1.y < corner2.y) {
                // Between up side and down side
                rect1.pos.x += corner2.x - rect1.pos.x;
            }
            else {
                // First rectangle is on the right side but below second rectangle
                if (corner2.x - rect1.pos.x <= corner2.y - rect1.pos.y) {
                    // If moving the rectangle to the right is less than moving below
                    rect1.pos.x += corner2.x - rect1.pos.x;
                }
                else {
                    rect1.pos.y += corner2.y - rect1.pos.y;
                }
            }
        }

        return true;
    }
}

#endif //_COLLISIONCALCULATOR_H
