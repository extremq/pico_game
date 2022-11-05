//
// Created by god on 30.10.2022.
//

#ifndef _ST7735_H
#define _ST7735_H

#include <cstdint>
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "Frame.h"
#include "ST7735_defines.h"

/*
 * Display.h contains all that's needed for displaying the game.
 * It is an extension of a frame. The frame only contains buffers
 * and matrix operations on that buffer, while Display.h takes care
 * of communicating with the ST7735 Controller
 */

class Display : public Frame {
private:
    static Display* _instance;

    uint8_t _spi_port;
    uint8_t _cs, _dc, _sda, _scl, _res; /* Pins on PCB */

    void init_pins(); /* Init functions */
    void init_lcd();

    void set_cs_voltage(bool value); /* Setters */
    void set_dc_voltage(bool value);
    void set_res_voltage(bool value);

    void write_cmd(uint8_t cmd); /* Write abstracts */
    void write_data(uint8_t* data, uint8_t len);

    void write_spi(uint8_t data); /* Spi writing */
    void write_spi_n(uint8_t* data, uint16_t n);

    void set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void reset();

    Display() {
        this->_cs = 0;
        this->_dc = 0;
        this->_res = 0;
        this->_spi_port = 0;
        this->_sda = 0;
        this->_scl = 0;
    }

public:
    static Display* get() {
        if (_instance == nullptr) {
            _instance = new Display;
        }
        return _instance;
    }

    void init(uint8_t w, uint8_t h, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res, uint8_t spi_port);
    void load_frame();
};


#endif //_ST7735_H
