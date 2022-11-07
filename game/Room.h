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

struct WallData {
    uint64_t id;
    Drawable* drawable;
};

#define WALL_SIZE 8

class Room {
private:
    uint8_t _tile_map[(128 / WALL_SIZE) * (128 / WALL_SIZE)] = {0};
    std::vector<WallData> _drawables;

    RoomCreator* creator = RoomCreator::get();
    GameEngine* engine = GameEngine::get();
    Collision* collision = Collision::get();
public:
    void generate(uint8_t seed) {
        creator->make_tile_map(this->_tile_map, (128 / WALL_SIZE), (128 / WALL_SIZE), seed);
    }

    void register_map() {
        for (uint8_t row = 0; row < (128 / WALL_SIZE); ++row) {
            for (uint8_t col = 0; col < (128 / WALL_SIZE); ++col) {
                if (this->_tile_map[col + row * (128 / WALL_SIZE)] == WALL) {
                    // Create a new wall and configure it
                    Wall* wall = new Wall;
                    wall->set_config(col * WALL_SIZE, row * WALL_SIZE, WALL_SIZE, WALL_SIZE, 0x0);

                    // Create a wall data that stores the id of the collidable and
                    // the pointer to the drawable object.
                    // Needed for cleanup.
                    WallData wall_data = {
                            collision->add_collidable(col * WALL_SIZE, row * WALL_SIZE, WALL_SIZE, WALL_SIZE),
                            wall
                    };
                    // Place in drawables in order to delete them
                    engine->register_drawable(wall);
                    _drawables.push_back(wall_data);
                }
            }
        }
    }

    void discard_map() {
        for (auto d : this->_drawables) {
            collision->remove_collidable(d.id);
            engine->discard_drawable(d.drawable->get_id());
            delete d.drawable;
        }
    }
};


#endif //_ROOM_H
