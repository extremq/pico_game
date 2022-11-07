//
// Created by god on 03.11.2022.
//

#include "GameEngine.h"
#include <iostream>

GameEngine* GameEngine::_instance = nullptr;

// Init all the needed modules.
void GameEngine::init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res,
                      uint8_t spi_port, uint8_t xpin, uint8_t ypin) {
    this->_display->init(w, h, cs, dc, sda, scl, res, spi_port);
    this->_joystick->init(xpin, ypin);
}

void GameEngine::start_engine() {
    bool running = true;
    while(running) {
        uint64_t start_frame = time_us_64();

        // Update time class
        this->_time->update_time(start_frame);

        // Take care of basic events
        for (auto it = this->_event_list.begin(); it != this->_event_list.end(); ++it) {
            // Check if object's end time is lower than current time
            if ((*it)->get_end_time_raw() <= start_frame) {
                (*it)->on_discard(); // Discard the object
                delete (*it); // (*it) is a pointer to class
                this->_event_list.erase(it--);
            }
            else
                (*it)->on_frame_update();
        }

        // Take care of drawables (this starts with the lowest layer)
        for (auto it = this->_drawable_list.begin(); it != this->_drawable_list.end(); ++it) {
            // Check if object's end time is lower than current time
            if ((*it)->get_end_time_raw() <= start_frame) {
                (*it)->on_discard(); // Discard the object
                delete (*it); // (*it) is a pointer to class
                this->_drawable_list.erase(it--);
            }
            else
                (*it)->on_frame_update();
        }

        // Send the frame to the display
        this->_display->load_frame();
        uint64_t diff = time_us_64() - start_frame;
        if (diff < 16000)
            sleep_us(16000 - diff);
    }
}

// Add drawable in set of drawables and set start time
uint64_t GameEngine::register_drawable(Drawable* d) {
    this->_drawable_list.insert(d);

    // Init time and call register function
    d->set_id(this->_id_cnt++);
    d->set_start_time_raw(time_us_64());
    d->on_register();

    return this->_id_cnt;
}

// Add event in vector of events and set start time
uint64_t GameEngine::register_event(Event* e) {
    this->_event_list.push_back(e);

    // Init time and call register function
    e->set_id(this->_id_cnt++);
    e->set_start_time_raw(time_us_64());
    e->on_register();

    return this->_id_cnt;
}

void GameEngine::discard_event(uint64_t id) {
    for (auto it = this->_event_list.begin(); it != this->_event_list.end(); ++it) {
        if ((*it)->get_id() == id) {
            this->_event_list.erase(it);
            return;
        }
    }
}

void GameEngine::discard_drawable(uint64_t id) {
    for (auto it = this->_drawable_list.begin(); it != this->_drawable_list.end(); ++it) {
        if ((*it)->get_id() == id) {
            this->_drawable_list.erase(it);
            return;
        }
    }
}
