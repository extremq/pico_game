//
// Created by god on 07.11.2022.
//

#ifndef _ROOMCREATOR_H
#define _ROOMCREATOR_H

#include <cstdint>

#define WALL 1
#define EXIT 2

class RoomCreator {
private:
    static RoomCreator* _instance;
    RoomCreator() = default;
public:
    static RoomCreator* get() {
        if (_instance == nullptr) {
            _instance = new RoomCreator;
        }
        return _instance;
    }

    void make_tile_map(uint8_t* tile_map_buf, uint16_t h, uint16_t w, uint8_t seed);

};


#endif //_ROOMCREATOR_H
