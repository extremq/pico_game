//
// Created by god on 31.10.2022.
//

#ifndef _FRAME_H
#define _FRAME_H

#include <cstdint>

/*
 * Class for operating on Frame buffers.
 *
 * Basically, all draws will be simulated in this _buffer instead of actually
 * sending them to the lcd ram. This way, I can compute a difference matrix
 * between the current Frame and the last Frame and only send different pixels.
 */

class Frame {
private:
    uint16_t* _last_frame;
    uint8_t _h, _w;
    uint16_t* _buffer;
    bool* _diff;
public:
    Frame();
    ~Frame();

    void init_frame(uint8_t h, uint8_t w);

    /* Getters for Display.h */
    uint16_t * get_buffer();
    bool* get_diff();
    uint8_t get_width();
    uint8_t get_height();

    void draw_rect(uint16_t col, uint16_t row, uint16_t h, uint16_t w, uint16_t color);
    void fill_rect(uint16_t col, uint16_t row, uint16_t h, uint16_t w, uint16_t color);
    void line_horiz(uint16_t col, uint16_t row, uint16_t l, uint16_t color);
    void line_verti(uint16_t col, uint16_t row, uint16_t l, uint16_t color);
    void draw_circle(uint16_t col, uint16_t row, uint16_t r, uint16_t color);
    void fill_circle(uint16_t col, uint16_t row, uint16_t r, uint16_t color);
    void draw_sprite(uint16_t col, uint16_t row, uint16_t h, uint16_t w, const uint16_t* sprite);
    void compute_diff();
};


#endif //_FRAME_H
