//
// Created by god on 07.11.2022.
//

#include "RoomCreator.h"

RoomCreator* RoomCreator::_instance = nullptr;

void RoomCreator::make_tile_map(uint8_t *tile_map_buf, uint16_t h, uint16_t w, uint8_t seed) {
    // Make a border
    for (uint16_t col = 0; col < w; ++col) {
        tile_map_buf[col] = WALL;
        tile_map_buf[col + (h - 1) * w] = WALL;
    }

    for (uint16_t row = 0; row < h; ++row) {
        tile_map_buf[row * w] = WALL;
        tile_map_buf[w - 1 + row * w] = WALL;
    }

    tile_map_buf[seed + 1 * w] = WALL;
    tile_map_buf[5 + 2 * w] = WALL;
    tile_map_buf[6 + 2 * w] = WALL;
    tile_map_buf[7 + 2 * w] = WALL;
    tile_map_buf[5 + 3 * w] = WALL;
    tile_map_buf[6 + 3 * w] = WALL;
    tile_map_buf[7 + 3 * w] = WALL;
    tile_map_buf[5 + 4 * w] = WALL;
    tile_map_buf[6 + 4 * w] = WALL;
    tile_map_buf[7 + 4 * w] = WALL;
}
