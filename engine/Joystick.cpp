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

uint16_t Joystick::get_x() {
    adc_select_input(0);
    return adc_read();
}

uint16_t Joystick::get_y() {
    adc_select_input(1);
    return adc_read();
}

int8_t Joystick::get_x_direction() {
    adc_select_input(0);
    uint16_t raw_x = adc_read();
    if (raw_x < mid_point - 100) return -1;
    if (raw_x < mid_point + 100) return 0;
    return 1;
}

int8_t Joystick::get_y_direction() {
    adc_select_input(1);
    uint16_t raw_y = adc_read();
    if (raw_y < mid_point - 100) return -1;
    if (raw_y < mid_point + 100) return 0;
    return 1;
}

// All these computations should be optimised by the compiler since they are const
double Joystick::get_x_direction_precise() {
    adc_select_input(0);
    double raw_x = adc_read();
    if (raw_x < 100) return -1;
    if (raw_x < mid_point_precise - 100) return - 1.0 + (raw_x - 100) / (mid_point_precise - 100);
    if (raw_x < mid_point_precise + 100) return 0.0;
    if (raw_x < max_value - 100)
        return (raw_x - (mid_point_precise + 100)) / (max_value - mid_point_precise);
    return 1.0;
}

double Joystick::get_y_direction_precise() {
    adc_select_input(1);
    double raw_y = adc_read();
    if (raw_y < 100) return -1;
    if (raw_y < mid_point_precise - 100) return - 1.0 + (raw_y - 100) / (mid_point_precise - 100);
    if (raw_y < mid_point_precise + 100) return 0.0;
    if (raw_y < max_value - 100)
        return (raw_y - (mid_point_precise + 100)) / (max_value - mid_point_precise);
    return 1.0;
}
