//
// Created by god on 03.11.2022.
//

#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include <vector>
#include <set>
#include "Drawable.h"
#include "Display.h"
#include "Joystick.h"
#include "Time.h"

struct cmp {
    bool operator() (const Drawable* a, const Drawable* b) const {
        return a->get_layer() < b->get_layer();
    }
};

// Singleton based GameEngine
class GameEngine {
private:
    static GameEngine* _instance;
    GameEngine() = default;
    uint64_t _id_cnt = 0; // Used for assigning a unique id to events and drawables

    Time* _time = Time::get();
    Display* _display = Display::get();
    Joystick* _joystick = Joystick::get();

    // Array of events.
    std::vector<Event*> _event_list;

    // Set of Drawable pointers based on layer
    std::multiset<Drawable*, cmp> _drawable_list;
public:
    // Return singleton instance
    static GameEngine* get() {
        if (_instance == nullptr) {
            _instance = new GameEngine;
        }
        return _instance;
    }
    uint64_t register_event(Event* e);
    uint64_t register_drawable(Drawable* d);
    void discard_event(uint64_t id);
    void discard_drawable(uint64_t id);
    void init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res,
              uint8_t spi_port, uint8_t xpin, uint8_t ypin);
    void start_engine();
};


#endif //_GAMEENGINE_H
