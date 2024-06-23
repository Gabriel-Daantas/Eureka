#include <fstream>
#include <string>
#include <iostream>
#include "Map.h"

Map::Map(){
    std::ifstream inFile("map.txt");
    std::string line;

    int i = 0;
    while (std::getline(inFile, line)) {
        for (auto c : line) {
            std::cout << c;
            map[i] = c - '0';
            i++;
        }
    }
}

int Map::getTile(int x, int y) const{
    if (x < 0 || x > MAP_SIZE || y < 0 || y > MAP_SIZE)
        return 0;

    int mapIndex = y * MAP_SIZE + x;

    return map[mapIndex];
}

void Map::setTile(int x, int y, int tile){
    if (x < 0 || x > MAP_SIZE || y < 0 || y > MAP_SIZE)
        return;

    int mapIndex = y * MAP_SIZE + x;

    map[mapIndex] = tile;
}