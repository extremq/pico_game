//
// Created by god on 05.11.2022.
//

#ifndef _TIME_H
#define _TIME_H


#include <cstdint>

class Time {
private:
    static Time* _instance;

    // In seconds
    double _game_time = 0;
    double _delta_time = 0;

    Time() = default;
public:
    static Time* get() {
        if (_instance == nullptr) {
            _instance = new Time;
        }
        return _instance;
    }
    void update_time(uint64_t raw_time) {
        // Even if i cast to double, it should have enough accuracy.
        double raw_time_seconds = raw_time / 1000000.0;
        this->_delta_time = raw_time_seconds - this->_game_time;
        this->_game_time = raw_time_seconds;
    }

    double get_game_time() {
        return this->_game_time;
    }

    double get_delta_time() {
        return this->_delta_time;
    }
};


#endif //_TIME_H
