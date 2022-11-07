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

class WorldManager : public Drawable {
private:
    static WorldManager* _instance;
    std::vector<Room*> _rooms;
    GameEngine* engine = GameEngine::get();
    Time* time = Time::get();
    Room* room_test = nullptr;
    WorldManager() = default;
    double _last_map = 0;
    int seed = 0;
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

        room_test = new Room;
        room_test->generate(seed);
        room_test->register_map();
//        this->_rooms.push_back(room_test);
    }

    void on_frame_update() override{
        if (time->get_game_time() - this->_last_map > 5.0) {
            std::cout << "a?\n";
            this->_last_map = time->get_game_time();
//            room_test->discard_map();
//            std::cout << "b\n";
//            delete room_test;
//            std::cout << "c\n";
//            room_test = new Room;
//            std::cout << "d\n";
//            room_test->generate(++seed);
//            std::cout << "e\n";
//            room_test->register_map();
//            std::cout << "f\n";
        }
    }
};


#endif //_WORLDMANAGER_H
