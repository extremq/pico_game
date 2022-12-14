//
// Created by god on 30.10.2022.
//

#include "Display.h"

Display* Display::_instance = nullptr;

/*
 * General init function
 */
void Display::init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc,
                   uint8_t sda, uint8_t scl, uint8_t res, uint8_t spi_port) {
    this->_cs = cs;
    this->_dc = dc;
    this->_sda = sda;
    this->_scl = scl;
    this->_res = res;
    this->_spi_port = spi_port;

    /* Inits */
    this->init_frame(h, w);
    this->init_pins();
    this->reset();
    this->init_lcd();
    this->load_frame();
}

void Display::init_pins() {
    spi_init(this->_spi_port == 0 ? spi0 : spi1, 20 * 1000 * 1000); // Set freq

    gpio_init(this->_sda);
    gpio_init(this->_scl);
    gpio_set_dir(this->_sda, GPIO_OUT);
    gpio_set_dir(this->_scl, GPIO_OUT);

    gpio_set_function(this->_sda, GPIO_FUNC_SPI); // Init _sda
    gpio_set_function(this->_scl, GPIO_FUNC_SPI); // Init scl

    gpio_init(this->_dc); // Init
    gpio_set_dir(this->_dc, GPIO_OUT);
    gpio_put(this->_dc, false);

    gpio_init(this->_cs); // Init cs
    gpio_set_dir(this->_cs, GPIO_OUT);
    gpio_put(this->_cs, true); // CS is active low

    gpio_init(this->_res);
    gpio_set_dir(this->_res, GPIO_OUT);
    gpio_put(this->_res, true); // RES is active low
}

/*
 * The ugly mess. Init the screen.
 * THIS DEPENDS ON LCD. PLEASE CHANGE
 * IF YOU WANT TO ADAPT IT TO YOUR LCD
 */
void Display::init_lcd() {
    uint8_t buf[16];
    this->write_cmd(ST77XX_SWRESET); // Software reset
    sleep_us(50);
    this->write_cmd(ST77XX_SLPOUT); // Out of sleep mode
    sleep_us(500);

    this->write_cmd(ST7735_FRMCTR1); // Frame rate control
    buf[0] = 0X01;
    buf[1] = 0X2C;
    buf[2] = 0X2D;
    this->write_data(buf, 3);

    this->write_cmd(ST7735_FRMCTR2); // Frame rate control
    this->write_data(buf, 3);

    this->write_cmd(ST7735_FRMCTR3); // Frame rate control
    this->write_data(buf, 3);
    sleep_us(10);

    this->write_cmd(ST7735_INVCTR); // diplay inversion control
    buf[0] = 0x07;
    this->write_data(buf, 1);

    this->write_cmd(ST7735_PWCTR1); // power control
    buf[0] = 0xA2;
    buf[1] = 0x02;
    buf[2] = 0x84;
    this->write_data(buf, 3);
    sleep_us(10);

    this->write_cmd(ST7735_PWCTR2); // power control
    buf[0] = 0xC5;
    this->write_data(buf, 1);

    this->write_cmd(ST7735_PWCTR3); // power control
    buf[0] = 0x0A;
    buf[1] = 0x00;
    this->write_data(buf, 2);

    this->write_cmd(ST7735_PWCTR4); // power control
    buf[0] = 0x8A;
    buf[1] = 0x2A;
    this->write_data(buf, 2);

    this->write_cmd(ST7735_PWCTR5); // power control
    buf[0] = 0x8A;
    buf[1] = 0xEE;
    this->write_data(buf, 2);

    this->write_cmd(ST7735_VMCTR1);
    buf[0] = 0x0E;
    this->write_data(buf, 1);
    sleep_us(10);

    this->write_cmd(ST77XX_MADCTL);
    buf[0] = 0xC8;
    this->write_data(buf, 1);

    this->write_cmd(ST7735_GMCTRP1); // Gamma control
    buf[0] = 0x02;
    buf[1] = 0x1c;
    buf[2] = 0x07;
    buf[3] = 0x12;
    buf[4] = 0x37;
    buf[5] = 0x32;
    buf[6] = 0x29;
    buf[7] = 0x2d;
    buf[8] = 0x29;
    buf[9] = 0x25;
    buf[10] = 0x2b;
    buf[11] = 0x39;
    buf[12] = 0x00;
    buf[13] = 0x01;
    buf[14] = 0x03;
    buf[15] = 0x10;
    this->write_data(buf, 16);
    sleep_us(10);

    this->write_cmd(ST7735_GMCTRN1);
    buf[0] = 0x03;
    buf[1] = 0x1d;
    buf[2] = 0x07;
    buf[3] = 0x06;
    buf[4] = 0x2e;
    buf[5] = 0x2c;
    buf[6] = 0x29;
    buf[7] = 0x2d;
    buf[8] = 0x2e;
    buf[9] = 0x2e;
    buf[10] = 0x37;
    buf[11] = 0x3f;
    buf[12] = 0x00;
    buf[13] = 0x00;
    buf[14] = 0x02;
    buf[15] = 0x10;
    this->write_data(buf, 16);
    sleep_us(10);

    this->write_cmd(ST77XX_CASET); // Column address set
    buf[0] = 0x00;
    buf[1] = X_START;
    buf[2] = 0x00;
    buf[3] = this->get_width() + X_START - 1;
    this->write_data(buf, 4);

    this->write_cmd(ST77XX_RASET); // Row address set
    buf[1] = Y_START;
    buf[3] = this->get_height()  + Y_START - 1;
    this->write_data(buf, 4);

    this->write_cmd(ST77XX_COLMOD); // Select 16 bit color
    buf[0] = 0x05;
    this->write_data(buf, 1);

    this->write_cmd(ST77XX_NORON); // Normal mode
    sleep_us(10);

    this->write_cmd(ST77XX_RAMWR);
    sleep_us(500);

    this->write_cmd(ST77XX_DISPON); // Display on
    sleep_us(500);
}

/* Helper functions */
void Display::set_cs_voltage(bool value) {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->_cs, value);
    asm volatile("nop \n nop \n nop");
}

void Display::set_dc_voltage(bool value) {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->_dc, value);
    asm volatile("nop \n nop \n nop");
}

void Display::set_res_voltage(bool value) {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->_res, value);
    asm volatile("nop \n nop \n nop");
}

/*
 * CS is low when we send data
 * DC selects either data or cmd
 */
void Display::write_cmd(uint8_t cmd) {
    this->set_dc_voltage(false);
    this->set_cs_voltage(false);
    this->write_spi(cmd);
    this->set_cs_voltage(true);
}

void Display::write_data(uint8_t* data, uint8_t len) {
    this->set_dc_voltage(true);
    this->set_cs_voltage(false);
    this->write_spi_n(data, len);
    this->set_cs_voltage(true);
}

/* SPI writing helper function */
inline void Display::write_spi(uint8_t data) {
    spi_write_blocking(this->_spi_port == 0 ? spi0 : spi1, &data, 1);
}

inline void Display::write_spi_n(uint8_t* data, uint16_t n) {
    spi_write_blocking(this->_spi_port == 0 ? spi0 : spi1, data, n);
}

/* Resetting function, as per datasheet */
void Display::reset() {
    this->set_res_voltage(true);
    sleep_ms(10);
    this->set_res_voltage(false);
    sleep_ms(10);
    this->set_res_voltage(true);
    sleep_ms(10);
}

/* End helper functions */

/*
 * SPI displays set an address window rectangle for blitting pixels
 * Parameter1:  x0 Top left corner x coordinate
 * Parameter2:  y0 Top left corner y coordinate
 * Parameter3:  x1 Lower right corner x coordinate
 * Parameter4:  y1 Lower right corner y coordinate
 * https://en.wikipedia.org/wiki/Bit_blit
 * Credits: https://github.com/bablokb/pico-st7735/
*/
void Display::set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    uint8_t buf[4];
    this->write_cmd(ST77XX_CASET); // Set column range
    buf[0] = X_START;
    buf[1] = x0 + X_START;
    buf[2] = X_START;
    buf[3] = x1 + X_START;
    this->write_data(buf, 4);

    this->write_cmd(ST77XX_RASET); // Set row range
    buf[0] = Y_START;
    buf[1] = y0 + Y_START;
    buf[2] = Y_START;
    buf[3] = y1 + Y_START;
    this->write_data(buf, 4);

    this->write_cmd(ST77XX_RAMWR);
}

void Display::load_frame() {
    // Commit changes to diff and buffers
    this->compute_diff();

    // Get buffers
    uint16_t * buff = this->get_buffer();
    bool * diff = this->get_diff();
    uint8_t w = this->get_width();
    uint8_t h = this->get_height();

    // Color bytes
    uint8_t color[2];

    for (uint16_t y = 0; y < h; ++y) {
        for (uint16_t x = 0; x < w; ++x) {
            if (!diff[x + y * w]) continue;

            // Get high and low bytes of color
            color[0] = buff[x + y * w] >> 8;
            color[1] = buff[x + y * w];

            // Set address window of 1 pixel
            this->set_addr_window(x, y, x, y);
            this->write_data(color, 2);
        }
    }
}
