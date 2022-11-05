//
// Created by god on 03.11.2022.
//

#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include <cstdint>
#include "hardware/adc.h"

class Joystick {
private:
    static Joystick* _instance;
    Joystick() = default;
    const uint16_t max_value = 4095;
public:

    uint16_t get_x();
    uint16_t get_y();

    // Return singleton instance
    static Joystick* get() {
        if (_instance == nullptr) {
            _instance = new Joystick;
        }
        return _instance;
    }

    uint16_t get_max_value() {
        return this->max_value;
    }

    // Returns 1, 0 or -1 depending on direction on that axis
    int8_t get_y_direction ();
    int8_t get_x_direction ();

    void init(uint8_t xpin, uint8_t ypin);

};


#endif //_JOYSTICK_H
