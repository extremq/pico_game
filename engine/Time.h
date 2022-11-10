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
    float _game_time = 0;
    float _delta_time = 0;

    Time() = default;

    // Should only be accessible by GameEngine
    void update_time(uint64_t raw_time) {
        // Even if i cast to double, it should have enough accuracy.
        float raw_time_seconds = raw_time / 1000000.0;
        this->_delta_time = raw_time_seconds - this->_game_time;
        this->_game_time = raw_time_seconds;
    }
public:
    static Time* get() {
        if (_instance == nullptr) {
            _instance = new Time;
        }
        return _instance;
    }

    float get_game_time() {
        return this->_game_time;
    }

    float get_delta_time() {
        return this->_delta_time;
    }

    friend class GameEngine;
};


#endif //_TIME_H
