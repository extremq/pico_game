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

// Singleton based GameEngine
class GameEngine {
private:
    static GameEngine* _instance;
    GameEngine() = default;

    // Array of events.
    std::vector<Event*> _event_list;

    // Set of Drawable pointers based on layer
    std::set<Drawable*> _drawable_list;
public:
    // Return singleton instance
    static GameEngine* get() {
        if (_instance == nullptr) {
            _instance = new GameEngine;
        }
        return _instance;
    }
    void register_event(Event* e);
    void register_drawable(Drawable* d);
    void init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res,
              uint8_t spi_port, uint8_t xpin, uint8_t ypin);
    void start_game();
};


#endif //_GAMEENGINE_H
