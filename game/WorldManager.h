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
#include "Ball.h"
#include "engine/Time.h"
#include "engine/Invokable.h"

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
            room->generate(i);
            room->init_room();

            this->_rooms.push_back(room);
        }

        this->_rooms[0]->register_colliders();
        this->_rooms[0]->register_drawables();
    }

    void add_circle() {
        Ball* circle = new Ball(70, 70, 10, 0x0);
        this->_rooms[0]->add_collidable(circle);
        this->_rooms[0]->register_for_drawing(circle);
        this->_rooms[0]->register_for_colliding(circle);
    }
    void add_wall() {
        Wall* wall = new Wall(40, 40, 30, 30, 0x0);
        this->_rooms[0]->add_collidable(wall);
        this->_rooms[0]->register_for_drawing(wall);
        this->_rooms[0]->register_for_colliding(wall);
    }


    void on_frame_update() override{
        if (time->get_game_time() - this->_last_map > 1) {
            this->_last_map = 100000000;
            new Invokable<WorldManager>(&WorldManager::add_circle, this, 2);
            new Invokable<WorldManager>(&WorldManager::add_wall, this, 3);
        }
    }
};


#endif //_WORLDMANAGER_H
