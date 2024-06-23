#include <SFML/Graphics.hpp>
#include <fstream>
#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "utils.h"
#include "Map.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window({ WINDOW_WIDTH, WINDOW_HEIGHT }, "RAYCAST");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Renderer drawBuffer;
    Map map;
    Player player;

    sf::RectangleShape crosshair;
    crosshair.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    crosshair.setSize({ 10, 10 });
    crosshair.setFillColor(sf::Color::Black);

    window.setMouseCursorGrabbed(true);

    Keyboard keyboard;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            keyboard.update(e);
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }
        if (keyboard.isKeyDown(sf::Keyboard::Key::Escape))
        {
            window.setMouseCursorGrabbed(false);
        }

        player.doInput(keyboard);

        window.clear();
        drawBuffer.clearPixels();

        // ================= Raycasting starts here ========================
        float rayAngle = wrap(player.angle - FOV / 2);
        for (int i = 0; i < WINDOW_WIDTH; i++) {

            sf::Vector2f horizonatalIntersect;
            sf::Vector2f verticalIntersect;

            // =============== Horizontal line =========================
            bool down = rayAngle < 180;
            {
                sf::Vector2f initialIntersect;
                initialIntersect.y = std::floor(player.y / TILE_SIZE) * TILE_SIZE +
                    (rayAngle < 180 ? TILE_SIZE : -1);
                initialIntersect.x =
                    (initialIntersect.y - player.y) / std::tan(rads(rayAngle)) + player.x;

                // Find distances to the next intersection
                sf::Vector2f distance;
                distance.y = rayAngle < 180 ? TILE_SIZE : -TILE_SIZE;
                distance.x = TILE_SIZE / (rayAngle < 180 ? std::tan(rads(rayAngle))
                    : -std::tan(rads(rayAngle)));

                int gridX = std::floor(initialIntersect.x / TILE_SIZE);
                int gridY = std::floor(initialIntersect.y / TILE_SIZE);
                sf::Vector2f next = initialIntersect;
                while ((gridX >= 0 && gridX < MAP_SIZE) &&
                    map.getTile(gridX, gridY) == 0) {
                    next += distance;
                    gridX = std::floor(next.x / TILE_SIZE);
                    gridY = std::floor(next.y / TILE_SIZE);
                }
                horizonatalIntersect = next;
            }

            bool left = rayAngle > 90 && rayAngle < 270;
            // =============== Vertical line =========================
            {

                sf::Vector2f initialIntersect;
                initialIntersect.x = std::floor(player.x / TILE_SIZE) * TILE_SIZE +
                    (left ? -1 : TILE_SIZE);
                initialIntersect.y =
                    (initialIntersect.x - player.x) * std::tan(rads(rayAngle)) + player.y;

                sf::Vector2f distance;
                distance.x = left ? -TILE_SIZE : TILE_SIZE;
                distance.y = TILE_SIZE * (left ? -std::tan(rads(rayAngle))
                    : std::tan(rads(rayAngle)));

                sf::Vector2f next = initialIntersect;
                int gridX = std::floor(next.x / TILE_SIZE);
                int gridY = std::floor(next.y / TILE_SIZE);

                while ((gridX >= 0 && gridX < MAP_SIZE) &&
                    map.getTile(gridX, gridY) == 0) {
                    next += distance;
                    gridX = std::floor(next.x / TILE_SIZE);
                    gridY = std::floor(next.y / TILE_SIZE);
                }
                verticalIntersect = next;
            }

            // Find the shortest distance
            float hDist = distance({ player.x, player.y }, horizonatalIntersect);
            float vDist = distance({ player.x, player.y }, verticalIntersect) - (left ? 1 : 0);
            float dist = 0;
            sf::Color colour;
            if (hDist < vDist) {
                dist = hDist;
                colour = { 255, 153, 51 };
            }
            else {
                dist = vDist;
                colour = { 255, 204, 102 };
            }

            // Draw the walls
            float height =
                TILE_SIZE / dist * (WINDOW_WIDTH / 2 / std::tan(rads(FOV / 2)));
            int start = (WINDOW_HEIGHT / 2) - height / 2;

            // Draw the ceiling, then the wall, then the floor
            // This is done by drawing vertical lines in a loop
            for (int y = 0; y < start; y++) {
                drawBuffer.setPixel(i, y, { 135, 206, 235 });
            }
            for (int y = start; y < start + height; y++) {
                drawBuffer.setPixel(i, y, { colour.r, colour.g, colour.b });
            }
            for (int y = start + height; y < WINDOW_HEIGHT; y++) {
                drawBuffer.setPixel(i, y, { 0, 153, 51 });
            }

            // Find the next ray angle
            rayAngle = wrap(rayAngle + (float)FOV / (float)WINDOW_WIDTH);

        }

        drawBuffer.render(window);

        window.draw(crosshair);

        window.display();
    }
}