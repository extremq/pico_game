//
// Created by god on 03.11.2022.
//

#ifndef _EVENT_H
#define _EVENT_H


#include <cstdint>

class Event {
private:
    uint64_t _start_time = 0;
    uint64_t _end_time = 0;
public:
    uint64_t get_start_time();
    uint64_t get_end_time();

    virtual void on_frame_update() {};
};


#endif //_EVENT_H
