//
// Created by god on 31.10.2022.
//

#include <cmath>
#include "frame.h"

uint16_t *frame::get_buffer() {
    return this->_buffer;
}

bool *frame::get_diff() {
    return this->_diff;
}

uint8_t frame::get_width() {
    return this->_w;
}

uint8_t frame::get_height() {
    return this->_h;
}

void frame::init(uint8_t h, uint8_t w) {
    this->_h = h;
    this->_w = w;
    this->_buffer = new uint16_t [w * h];
    this->_last_frame = new uint16_t [w * h];
    this->_diff = new bool [w * h];

    // Set buffer to black, while also setting
    // last frame to some other value. We don't
    // want them to be the same otherwise we
    // can't init the first screen.

    for (uint16_t i = 0; i < w * h; ++i) {
        this->_buffer[i] = 0xffff;
        this->_last_frame[i] = 0;
    }
}

// Safely deallocate memory
frame::~frame() {
    delete [] this->_buffer;
    delete [] this->_last_frame;
    delete [] this->_diff;
}

// Compute difference between frame and last_frame in the diff matrix
void frame::compute_diff() {
    for (uint16_t i = 0; i < this->_h * this->_w; ++i) {
        // If the pixel is different, then diff is one there.
        this->_diff[i] = (this->_buffer[i] != this->_last_frame[i]);
        this->_last_frame[i] = this->_buffer[i];
    }
}

// Fill a rectangle in the frame buffer using memset
void frame::fill_rect(uint16_t col, uint16_t row, uint16_t w, uint16_t h, uint16_t color) {
    // Validity checks
    if (col >= this->_w || row >= this->_h) return;
    if (w < 1 || h < 1) return;

    // Clamping
    if (col + w > this->_w)
        w = this->_w - col;

    if (row + h > this->_h)
        h = this->_h - row;

    // Loop and modify buffer
    for (uint16_t y = row; y < row + h; ++y) {
        for (uint16_t x = col; x < col + w; ++x) {
            this->_buffer[x + y * this->_w] = color;
        }
    }
}

// Draw a horizontal line.
void frame::line_horiz(uint16_t col, uint16_t row, uint16_t l, uint16_t color) {
    // Validity checks
    if (col >= this->_w || col >= this->_h) return;
    if (l < 1) return;

    if (col + l > this->_w)
        l = this->_w - col;

    for (uint16_t x = col; x < col + l; ++x) {
        this->_buffer[x + row * this->_w] = color;
    }
}

// Draw a vertical line.
void frame::line_verti(uint16_t col, uint16_t row, uint16_t l, uint16_t color) {
    // Validity checks
    if (col >= this->_w || col >= this->_h) return;
    if (l < 1) return;

    if (row + l > this->_h)
        l = this->_h - row;

    for (uint16_t y = row; y < row + l; ++y) {
        this->_buffer[col + y * this->_w] = color;
    }
}

void frame::draw_rect(uint16_t col, uint16_t row, uint16_t w, uint16_t h, uint16_t color) {
    // Validity checks
    if (col >= this->_w || row >= this->_h) return;
    if (w < 1 || h < 1) return;

    // Clamping
    if (col + w > this->_w)
        w = this->_w - col;

    if (row + h > this->_h)
        h = this->_h - row;

    for (uint16_t x = col; x < col + w; ++x) {
        this->_buffer[x + row * this->_w] = color;
        this->_buffer[x + (row + h - 1) * this->_w] = color;
    }

    for (uint16_t y = row; y < row + h; ++y) {
        this->_buffer[col + y * this->_w] = color;
        this->_buffer[col + w - 1 + y * this->_w] = color;
    }
}

// Pretty expensive? Should use sprites instead.
void frame::draw_circle(uint16_t col, uint16_t row, uint16_t r, uint16_t color) {
    // Validity checks
    if (col > this->_w || row > this->_h) return;

    // Consider col and row the origin point of the circle.
    int32_t x_col, col_x;
    int32_t y_row, row_y;
    for(int32_t y = row - r; y <= row; ++y) {
        for (int32_t x = col - r; x <= col; ++x) {
            x_col = x - col;
            y_row = y - row;
            col_x = 2 * col - x;
            row_y = 2 * row - y;
            if (fabs(x_col * x_col * 1.0 + y_row * y_row * 1.0 - r * r * 1.0) < r) {
                if (x < this->_w && y < this->_h && x >= 0 && y >= 0)
                    this->_buffer[x + y * this->_w] = color;

                if (2 * col - x < this->_w && y < this->_h && col_x >= 0 && y >= 0)
                    this->_buffer[col_x + y * this->_w] = color;

                if (x < this->_w && row_y < this->_h && x >= 0 && row_y >= 0)
                    this->_buffer[x + row_y * this->_w] = color;

                if (col_x < this->_w && row_y < this->_h && col_x >= 0 && row_y >= 0)
                    this->_buffer[col_x + row_y * this->_w] = color;
            }
        }
    }
}

void frame::fill_circle(uint16_t col, uint16_t row, uint16_t r, uint16_t color) {
    // Validity checks
    if (col > this->_w || row > this->_h) return;

    // Consider col and row the origin point of the circle.
    int32_t x_col, col_x;
    int32_t y_row, row_y;
    for(int32_t y = row - r; y <= row; ++y) {
        for (int32_t x = col - r; x <= col; ++x) {
            x_col = x - col;
            y_row = y - row;
            col_x = 2 * col - x;
            row_y = 2 * row - y;
            if ((x_col * x_col * 1.0 + y_row * y_row * 1.0 - r * r * 1.0) < r) {
                if (x < this->_w && y < this->_h && x >= 0 && y >= 0)
                    this->_buffer[x + y * this->_w] = color;

                if (2 * col - x < this->_w && y < this->_h && col_x >= 0 && y >= 0)
                    this->_buffer[col_x + y * this->_w] = color;

                if (x < this->_w && row_y < this->_h && x >= 0 && row_y >= 0)
                    this->_buffer[x + row_y * this->_w] = color;

                if (col_x < this->_w && row_y < this->_h && col_x >= 0 && row_y >= 0)
                    this->_buffer[col_x + row_y * this->_w] = color;
            }
        }
    }
}

void frame::draw_sprite(uint16_t col, uint16_t row, uint16_t w, uint16_t h, uint16_t *sprite) {

}

frame::frame() {
    this->_w = 0;
    this->_h = 0;
    this->_buffer = nullptr;
    this->_last_frame = nullptr;
    this->_diff = nullptr;
}

