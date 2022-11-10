//
// Created by god on 03.11.2022.
//

#ifndef _EVENT_H
#define _EVENT_H

#include <cstdint>

// The basic building block
class Event {
private:
    // In microseconds
    uint64_t _id = 1;
    uint64_t _start_time = 0x0000000000000000; // Microsecond 0
    uint64_t _end_time   = 0xffffffffffffffff; // Year ~6 million after microsecond 0

    void set_id(uint64_t);
public:
    // Raw returns in microseconds
    // Otherwise return double in seconds.
    uint64_t get_start_time_raw();
    uint64_t get_end_time_raw(int i);
    double get_start_time();
    double get_end_time();
    void set_start_time_raw(uint64_t time);
    void set_end_time_raw(uint64_t time);
    void set_start_time(double time);
    void set_end_time(double time);
    uint64_t get_id();

    // Called each frame
    virtual void on_frame_update() {};

    // Called when registered by the engine
    // PLEASE use this instead of a constructor
    // To make sure the start time is correct
    virtual void on_register() {};

    // Called when discarded by the game engine
    virtual void on_discard() {};

    // Only let the id to be set by the GameEngine
    friend class GameEngine;
};


#endif //_EVENT_H
