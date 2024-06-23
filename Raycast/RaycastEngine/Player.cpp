#include "Player.h"
#include "utils.h"

Player::Player(){
    rayCastSprite.setRadius({ 5.0f });
    dx = std::cos(angle);
    dy = std::sin(angle);
}

void Player::doInput(const Keyboard & keys){

    float a = rads(angle);
    if (keys.isKeyDown(sf::Keyboard::W)) {
            x += dx * SPEED;
            y += dy * SPEED;
    }
    if (keys.isKeyDown(sf::Keyboard::A)) {
        angle -= SPEED;
        if (angle < 0) {
            angle += 360;
        }
        dx = std::cos(a);
        dy = std::sin(a);
    }
    if (keys.isKeyDown(sf::Keyboard::S)) {
        x -= dx * SPEED;
        y -= dy * SPEED;
    }
    if (keys.isKeyDown(sf::Keyboard::D)) {
        angle += SPEED;
        if (angle > 360) {
            angle -= 360;
        }
        dx = std::cos(a);
            dy = std::sin(a);
    }
}

void Player::draw(sf::RenderTexture& window){
    rayCastSprite.setPosition(x / MINIMAP_SCALE - 5, y / MINIMAP_SCALE - 5);
    window.draw(rayCastSprite);
}
