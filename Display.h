//
// Created by god on 03.11.2022.
//

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "ST7735.h"

class Display {
private:
    static Display* _instance;
    Display() = default;

    ST7735 _display;
public:
    static Display* get() {
        if (_instance == nullptr) {
            _instance = new Display;
        }
        return _instance;
    }

    // Init the display
    inline void init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res, uint8_t spi_port) {
        this->_display.init(h, w, cs, dc, sda, scl, res, spi_port);
    }

    // Use some features of the Controller
    inline void draw_rect(uint16_t col, uint16_t row, uint16_t w, uint16_t h, uint16_t color) {
        this->_display.draw_rect(col, row, w, h, color);
    }

    inline void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
        this->_display.fill_rect(x, y, w, h, color);
    }

    inline void line_horiz(uint16_t col, uint16_t row, uint16_t l, uint16_t color) {
        this->_display.line_horiz(col, row, l, color);
    }

    inline void line_verti(uint16_t col, uint16_t row, uint16_t l, uint16_t color) {
        this->_display.line_verti(col, row, l, color);
    }

    inline void draw_sprite(uint16_t col, uint16_t row, uint16_t w, uint16_t h, uint16_t* sprite) {
        this->_display.draw_sprite(col, row, w, h, sprite);
    }

    inline void load_frame() {
        this->_display.load_frame();
    }
};


#endif //_DISPLAY_H
