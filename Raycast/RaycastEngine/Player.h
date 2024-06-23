#pragma once
#include <SFML/Graphics.hpp>
#include "Keyboard.h"

class Player {


public:
    float x = 153;
    float y = 221;
    float angle = 0;

    float dx = 0;
    float dy = 0;

    sf::CircleShape rayCastSprite;

    Player();
    void doInput(const Keyboard& keys);
    void draw(sf::RenderTexture& window);
};