//
// Created by god on 03.11.2022.
//

#include "GameEngine.h"

GameEngine* GameEngine::_instance = nullptr;

// Add event in vector of events
void GameEngine::register_event(Event* e) {
    this->_event_list.emplace_back(e);
}

// Init all the needed modules.
void GameEngine::init(uint8_t h, uint8_t w, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res,
                      uint8_t spi_port, uint8_t xpin, uint8_t ypin) {
    Display::get()->init(h, w, cs, dc, sda, scl, res, spi_port);
    Joystick::get()->init(xpin, ypin);
}
