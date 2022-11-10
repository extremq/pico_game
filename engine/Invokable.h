//
// Created by god on 08.11.2022.
//

#ifndef _INVOKABLE_H
#define _INVOKABLE_H

#include <iostream>
#include "Event.h"
#include "Time.h"
#include "GameEngine.h"

template <class T>
class Invokable : public Event {
private:
    void (T::* _func)() = nullptr;
    T* _ptr_T = nullptr;
    float _delay;
public:
    Invokable(void (T::* func)(), T* ptr_T, float delay_seconds) {
        // Register the event
        // This will set the start_time
        // I do this because the object will be registered in the next frame
        // either way
        // After all, if I wanted something this instant, why use an invokable?
        GameEngine::get()->register_event(this);

        this->_delay = delay_seconds;

        // Set function and pointer to class
        this->_func = func;
        this->_ptr_T = ptr_T;
    }

    void on_discard() override {
        // Call the function when event lifetime expires
        (*(this->_ptr_T).*_func)();
    }

    void on_register() override {
        // Set its end time to reflect the delay
        this->set_end_time(this->get_start_time() + this->_delay);
    }
};

#endif //_INVOKABLE_H
