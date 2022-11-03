//
// Created by god on 30.10.2022.
//

#ifndef _ST7735_H
#define _ST7735_H

/*
 * Copied defines from adafruit's libarry.
 * https://github.com/adafruit/Adafruit-ST7735-Library
 */
#include <cstdint>
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "Frame.h"

#define X_START 2
#define Y_START 3

#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD

// Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00

// Some register settings
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

class ST7735 {
private:
    uint8_t spi_port, height, width;
    uint8_t cs, dc, sda, scl, res; /* Pins on PCB */
    Frame screen_frame;

    void init_pins(); /* Init functions */
    void init_lcd();

    void set_cs(bool value); /* Setters */
    void set_dc(bool value);
    void set_res(bool value);

    void write_cmd(uint8_t cmd); /* Write abstracts */
    void write_data(uint8_t* data, uint8_t len);

    void write_spi(uint8_t data); /* Spi writing */
    void write_spi_n(uint8_t* data, uint16_t n);

    void set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void reset();

public:
    ST7735();

    void init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res, uint8_t spi_port);

    /* Inlining redirecting calls */
    inline void draw_rect(uint16_t col, uint16_t row, uint16_t w, uint16_t h, uint16_t color) {
        this->screen_frame.draw_rect(col, row, w, h, color);
    }

    inline void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
        this->screen_frame.fill_rect(x, y, w, h, color);
    }

    inline void line_horiz(uint16_t col, uint16_t row, uint16_t l, uint16_t color) {
        this->screen_frame.line_horiz(col, row, l, color);
    }

    inline void line_verti(uint16_t col, uint16_t row, uint16_t l, uint16_t color) {
        this->screen_frame.line_verti(col, row, l, color);
    }

    inline void draw_circle(uint16_t col, uint16_t row, uint16_t r, uint16_t color) {
        this->screen_frame.draw_circle(col, row, r, color);
    }

    inline void fill_circle(uint16_t col, uint16_t row, uint16_t r, uint16_t color) {
        this->screen_frame.fill_circle(col, row, r, color);
    }

    void load_frame();
};


#endif //_ST7735_H
