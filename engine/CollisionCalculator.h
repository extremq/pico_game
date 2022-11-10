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
    static bool is_intersecting_rect_rect(Rectangle* rect1,
                                          Rectangle* rect2) {
        double x0 = rect1->get_x(), y0 = rect1->get_y();
        double h0 = rect1->get_height(), w0 = rect1->get_width();
        double x1 = rect2->get_x(), y1 = rect2->get_y();
        double h1 = rect2->get_height(), w1 = rect2->get_width();

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

        // Update the colliders
        rect1->add_collider_to_queue(rect2);
        rect2->add_collider_to_queue(rect1);
        return true;
    }

    static double euclidian_distance(double x0, double y0,
                                     double x1, double y1) {
        return std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
    }

    static bool solve_collision_circle_circle(Circle* circle1,
                                              Circle* circle2) {
        double x0 = circle1->get_x(), y0 = circle1->get_y();
        double r0 = circle1->get_radius();
        double x1 = circle2->get_x(), y1 = circle2->get_y();
        double r1 = circle2->get_radius();

        double dist = euclidian_distance(x0, y0, x1, y1);

        // Isn't intersecting
        if (dist > r0 + r1) return false;

        // Update the collider queues
        circle1->add_collider_to_queue(circle2);
        circle2->add_collider_to_queue(circle1);

        // If the circles are on the same x
        // This is to avoid division by 0
        if (std::abs(x1 - x0) < 1e-5) {
            y0 = y0 > y1 ? y1 + r0 + r1 : y1 - r0 + r1;
            circle1->set_y(y0);
        }
        else {
            // get the vector from the center of circle2 that points
            // to center of circle1
            // normalize it and multiply it by the sum of radii
            double nx = (x1 - x0) / dist;
            double ny = (y1 - y0) / dist;

            x0 = x1 - (r0 + r1) * nx;
            y0 = y1 - (r0 + r1) * ny;

            // now just subtract from the first circle
            circle1->set_xy(x0, y0);
        }

        return true;
    }

    static bool solve_collision_rect_rect(Rectangle* rect1,
                                          Rectangle* rect2) {
        double x0 = rect1->get_x(), y0 = rect1->get_y();
        double h0 = rect1->get_height(), w0 = rect1->get_width();
        double x1 = rect2->get_x(), y1 = rect2->get_y();
        double h1 = rect2->get_height(), w1 = rect2->get_width();

        // Where should Rect 1 (x0, y0, h0, w0) be placed in order to clamp the intersection?

        // Get right corners
        double x0_s = x0 + w0;
        double y0_s = y0 + h0;
        double x1_s = x1 + w1;
        double y1_s = y1 + h1;

        // Rectangles are separated on x
        if (x0 > x1_s || x1 > x0_s) return false;

        // Rectangles are separated on y
        if (y0_s < y1 || y1_s < y0) return false;

        // This means we intersected.
        // Update the collider queues
        rect1->add_collider_to_queue(rect2);
        rect2->add_collider_to_queue(rect1);

        // Act as an intersection check if the second Rectangle isn't based
        // on physical collision
        if (rect2->get_type() != COLLISION)
            return true;

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

        rect1->set_xy(x0, y0);

        return true;
    }
}

#endif //_COLLISIONCALCULATOR_H
