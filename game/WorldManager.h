//
// Created by god on 07.11.2022.
//

#ifndef _WORLDMANAGER_H
#define _WORLDMANAGER_H

#include "engine/Drawable.h"
#include "testPlayer.h"
#include "Background.h"
#include "engine/GameEngine.h"
#include "Room.h"
#include "engine/Time.h"

class WorldManager : public Event {
private:
    static WorldManager* _instance;
    std::vector<Room*> _rooms;

    GameEngine* engine = GameEngine::get();
    Time* time = Time::get();

    WorldManager() = default;
    double _last_map = 0;
public:
    static WorldManager* get() {
        if (_instance == nullptr) {
            _instance = new WorldManager;
        }
        return _instance;
    }

    void on_register() override {
        testPlayer* player = new testPlayer;
        Background* background = new Background;
        engine->register_drawable(player);
        engine->register_drawable(background);

        for (uint8_t i = 0; i < 2; ++i) {
            Room* room = new Room;
            room->generate(1);
            room->make_room();

            this->_rooms.push_back(room);
        }
    }

    void on_frame_update() override{
        if (time->get_game_time() - this->_last_map > 5.0) {
            this->_last_map = 100000000;
            this->_rooms[0]->register_colliders();
            this->_rooms[0]->register_drawables();
        }
    }
};


#endif //_WORLDMANAGER_H
