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
public:
    const uint16_t max_value = 4095;

    uint16_t x();
    uint16_t y();

    // Return singleton instance
    static Joystick* get() {
        if (_instance == nullptr) {
            _instance = new Joystick;
        }
        return _instance;
    }
    void init(uint8_t xpin, uint8_t ypin);

};


#endif //_JOYSTICK_H
