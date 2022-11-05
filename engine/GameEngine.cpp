//
// Created by god on 03.11.2022.
//

#include "GameEngine.h"
#include <iostream>

GameEngine* GameEngine::_instance = nullptr;

// Add event in vector of events
void GameEngine::register_event(Event* e) {
    this->_event_list.push_back(e);
}

// Init all the needed modules.
void GameEngine::init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res,
                      uint8_t spi_port, uint8_t xpin, uint8_t ypin) {
    this->_display->init(w, h, cs, dc, sda, scl, res, spi_port);
    this->_joystick->init(xpin, ypin);
}

void GameEngine::start_game() {
    bool running = true;
    while(running) {
        uint64_t start_frame = time_us_64();

        // Update time class
        this->_time->update_time(start_frame);

        // Take care of basic events
        for (auto e : this->_event_list) {
            e->on_frame_update();
        }

        // Take care of drawables (this starts with the lowest layer)
        std::cout << "Layers:\n";
        for (auto d : this->_drawable_list) {
            std::cout << d->get_layer() << '\n';
            d->on_frame_update();
        }

        this->_display->load_frame();
        uint64_t diff = time_us_64() - start_frame;
        if (diff < 16000)
            sleep_us(16000 - diff);
    }
}

// Add drawable in set of drawables
void GameEngine::register_drawable(Drawable* d) {
    this->_drawable_list.insert(d);
}
