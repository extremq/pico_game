//
// Created by god on 03.11.2022.
//

#include "Joystick.h"

Joystick* Joystick::_instance = nullptr;

// Init the analog to digital converter pins
void Joystick::init(uint8_t xpin, uint8_t ypin) {
    adc_init();
    adc_gpio_init(xpin);
    adc_gpio_init(ypin);
}

uint16_t Joystick::x() {
    adc_select_input(0);
    return adc_read();
}

uint16_t Joystick::y() {
    adc_select_input(1);
    return adc_read();
}
