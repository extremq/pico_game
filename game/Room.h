//
// Created by god on 07.11.2022.
//

#ifndef _ROOM_H
#define _ROOM_H

#include <vector>
#include "engine/Drawable.h"
#include "RoomCreator.h"
#include "engine/GameEngine.h"
#include "engine/CollisionManager.h"
#include "Wall.h"

#define WALL_SIZE 8

class Room {
private:
    // The tile map is only used for initialization purposes
    // You shouldn't try to update the map using the _tile_map
    // and init map.
    uint8_t _tile_map[(128 / WALL_SIZE) * (128 / WALL_SIZE)] = {0};
    std::vector<Collidable*> _room_collidables;

    RoomCreator* creator = RoomCreator::get();
    GameEngine* engine = GameEngine::get();
    CollisionManager* collision = CollisionManager::get();
public:
    void generate(uint8_t seed) {
        creator->make_tile_map(this->_tile_map, (128 / WALL_SIZE), (128 / WALL_SIZE), seed);
    }

    uint8_t* get_tile_map() {
        return this->_tile_map;
    }

    void add_collidable(Collidable* collidable) {
        // Don't assume we want to use it for colliding or drawing
        // request the user to manually do so
        this->_room_collidables.push_back(collidable);
    }

    void register_for_colliding(Collidable* collidable) {
        collision->register_collidable(collidable);
    }

    void discard_for_colliding(Collidable* collidable) {
        collision->discard_collidable(collidable);
    }

    void register_for_drawing(Collidable* collidable) {
        engine->register_drawable(collidable);
    }

    void discard_for_drawing(Collidable* collidable) {
        engine->discard_drawable(collidable);
    }

    // All register functions should be used sparingly.
    void register_drawables() {
        // Register the drawing
        // Used if you want to display the map
        for (auto collidable : this->_room_collidables) {
            engine->register_drawable(collidable);
        }
    }

    void discard_drawables() {
        // Used for discarding the drawing
        // Useful if you dont want to render the map, but reuse it later
        for (auto collidable : this->_room_collidables) {
            engine->discard_drawable(collidable);
        }
    }

    void reset_drawables_and_colliders() {
        // Used for completely emptying the map
        for (auto collidable : this->_room_collidables) {
            engine->discard_drawable(collidable);
            collision->discard_collidable(collidable);
            delete collidable;
        }
        this->_room_collidables.clear();
    }

    void register_colliders() {
        for (auto collidable : this->_room_collidables) {
            collision->register_collidable(collidable);
        }
    }

    void discard_colliders() {
        for (auto collidable : this->_room_collidables) {
            collision->discard_collidable(collidable);
        }
    }

    void init_room() {
        // Remove drawables, free memory and clear the vector
        this->reset_drawables_and_colliders();
        // Create room
        for (uint8_t row = 0; row < (128 / WALL_SIZE); ++row) {
            for (uint8_t col = 0; col < (128 / WALL_SIZE); ++col) {
                if (this->_tile_map[col + row * (128 / WALL_SIZE)] == WALL) {
                    // Create a new wall and configure it
                    Wall* wall = new Wall(col * WALL_SIZE, row * WALL_SIZE, WALL_SIZE, WALL_SIZE, 0x0);

                    // Place in drawables in order to delete them later
                    this->_room_collidables.push_back(wall);
                }
            }
        }
    }
};


#endif //_ROOM_H
