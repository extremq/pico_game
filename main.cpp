#include <iostream>

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "ST7735.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

int main() {
    stdio_init_all();
    adc_init();

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);

    adc_gpio_init(26);
    adc_gpio_init(27);

    ST7735 display;
    display.init(HEIGHT, WIDTH, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES, 0);
    const uint16_t adc_max = 4095;

    while(1) {
        uint64_t start_frame = time_us_64();
        adc_select_input(0);
        uint32_t adc_x_raw = adc_read();
        adc_select_input(1);
        uint32_t adc_y_raw = adc_read();

        display.fill_rect(0, 0, WIDTH, HEIGHT, 0x0);
        display.fill_circle(adc_x_raw * 127 / adc_max, adc_y_raw * 127 / adc_max, 3, 0x1512);

        uint64_t diff = time_us_64() - start_frame;
        sleep_us(16000 - diff);
        display.load_frame();
    }
}
