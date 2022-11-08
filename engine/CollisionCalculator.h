//
// Created by god on 08.11.2022.
//

#ifndef _COLLISIONCALCULATOR_H
#define _COLLISIONCALCULATOR_H

#include "Rectangle.h"

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
        rect1->on_intersect(rect2);
        rect2->on_intersect(rect1);
        return true;
    }

    static void solve_collision_rect_rect(Rectangle* rect1,
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
        if (x0 > x1_s || x1 > x0_s) return;

        // Rectangles are separated on y
        if (y0_s < y1 || y1_s < y0) return;

        // This means we intersected.
        // Update the collider
        rect1->on_intersect(rect2);
        rect2->on_intersect(rect1);

        // Act as an intersection check if the second Rectangle isn't based
        // on physical collision
        if (rect2->get_type() != COLLISION)
            return;

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
    }
}

#endif //_COLLISIONCALCULATOR_H
