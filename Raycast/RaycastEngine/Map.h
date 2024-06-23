#pragma once
#include "utils.h"

class Map {
public:
    int map[MAP_SIZE * MAP_SIZE];

    Map();

    int getTile(int x, int y) const;

    void setTile(int x, int y, int tile);
};