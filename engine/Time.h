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
    double _physics_time = 0.0;
    double _delta_physics_time = 0.0;
    double _physics_timescale = 1.0;

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
        this->_delta_physics_time = raw_time_seconds * this->_physics_timescale - this->_physics_time;
        this->_game_time = raw_time_seconds;
        this->_physics_time = raw_time_seconds * this->_physics_timescale;
    }

    double get_game_time() {
        return this->_game_time;
    }

    double get_physics_time() {
        return this->_physics_time;
    }

    void set_timescale(double timescale) {
        this->_physics_timescale = timescale;
    }

    double get_delta_time() {
        return this->_delta_time;
    }

    double get_delta_physics_time() {
        return this->_delta_physics_time;
    }
};


#endif //_TIME_H
