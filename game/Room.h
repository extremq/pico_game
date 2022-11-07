//
// Created by god on 07.11.2022.
//

#ifndef _ROOM_H
#define _ROOM_H

#include <vector>
#include "engine/Drawable.h"
#include "RoomCreator.h"
#include "engine/GameEngine.h"
#include "engine/Collision.h"
#include "Wall.h"

#define WALL_SIZE 8

class Room {
private:
    uint8_t _tile_map[(128 / WALL_SIZE) * (128 / WALL_SIZE)] = {0};
    std::vector<Collidable*> _walls;

    RoomCreator* creator = RoomCreator::get();
    GameEngine* engine = GameEngine::get();
    Collision* collision = Collision::get();
public:
    void generate(uint8_t seed) {
        creator->make_tile_map(this->_tile_map, (128 / WALL_SIZE), (128 / WALL_SIZE), seed);
    }

    uint8_t* get_tile_map() {
        return this->_tile_map;
    }

    void register_drawables() {
        // Register drawable walls
        // Used if you want to display the map
        for (auto collideable : this->_walls) {
            engine->register_drawable(collideable);
        }
    }

    void discard_drawables() {
        // Used for discarding the drawable walls
        // Useful if you dont want to render the map, but reuse it later
        for (auto collideable : this->_walls) {
            engine->discard_drawable(collideable->get_id());
        }
    }

    void reset_drawables_and_colliders() {
        // Used for completely emptying the map
        for (auto collideable : this->_walls) {
            engine->discard_drawable(collideable->get_id());
            collision->discard_collidable(collideable->get_collision_id());
            delete collideable;
        }
        this->_walls.clear();
    }

    void register_colliders() {
        for (auto collideable : this->_walls) {
            collision->register_collidable(collideable->get_x(), collideable->get_y(),
                                           collideable->get_height(), collideable->get_width());
        }
    }

    void discard_colliders() {
        for (auto collideable : this->_walls) {
            collision->discard_collidable(collideable->get_collision_id());
        }
    }

    void make_room() {
        // Remove drawables, free memory and clear the vector
        this->reset_drawables_and_colliders();
        // Create room
        for (uint8_t row = 0; row < (128 / WALL_SIZE); ++row) {
            for (uint8_t col = 0; col < (128 / WALL_SIZE); ++col) {
                if (this->_tile_map[col + row * (128 / WALL_SIZE)] == WALL) {
                    // Create a new wall and configure it
                    Wall* wall = new Wall;
                    wall->set_config(col * WALL_SIZE, row * WALL_SIZE, WALL_SIZE, WALL_SIZE, 0x0);

                    // Place in drawables in order to delete them later
                    this->_walls.push_back(wall);
                }
            }
        }
    }
};


#endif //_ROOM_H
