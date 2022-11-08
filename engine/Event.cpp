//
// Created by god on 03.11.2022.
//

#include "Event.h"

uint64_t Event::get_start_time_raw() {
    return this->_start_time;
}

uint64_t Event::get_end_time_raw(int i) {
    return this->_end_time;
}

void Event::set_start_time_raw(uint64_t time) {
    this->_start_time = time;
}

void Event::set_end_time_raw(uint64_t time) {
    this->_end_time = time;
}

double Event::get_start_time() {
    return this->_start_time / 1000000.0;
}

double Event::get_end_time() {
    return this->_end_time / 1000000.0;
}

void Event::set_start_time(double time) {
    this->_start_time = time * 1000000.0;
}

void Event::set_end_time(double time) {
    this->_end_time = time * 1000000.0;
}

void Event::set_id(uint64_t id) {
    this->_id = id;
}

uint64_t Event::get_id() {
    return this->_id;
}
