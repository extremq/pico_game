//
// Created by god on 03.11.2022.
//

#ifndef _EVENT_H
#define _EVENT_H


#include <cstdint>

class Event {
public:
    uint64_t start_time;
    uint64_t end_time;

    virtual void on_frame_update();
    virtual void on_init();
    virtual void on_destroy();
};


#endif //_EVENT_H
