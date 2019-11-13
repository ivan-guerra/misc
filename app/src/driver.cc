#include <cassert>
#include <cstdio>
#include <utility>
#include <windows.h>

#include "Alien.h"
#include "AlienList.h"
#include "Playership.h"
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"

const int WIDTH = 640;
const int HEIGHT = 480;

int APIENTRY WinMain(
        HINSTANCE instance,
        HINSTANCE previousInstance,
        LPSTR commandLine,
        int commandShow)
{
    // Create engine
    DiceInvadersLib lib("DiceInvaders.dll");
    IDiceInvaders* engine = lib.get();

    // Initialize the window
    std::pair<uint32_t,uint32_t> screen_res() = std::make_pair(WIDTH, HEIGHT);
    engine->init(screen_res.first, screen_res.second);

    // Create all sprites
    ISprite* player_ship_sprite = engine->createSprite("data/player.bmp");
    ISprite* alien_sprite = engine->createSprite("data/enemy1.bmp");
    ISprite* rocket_sprite = engine->createSprite("data/rocket.bmp");
    ISprite* bomb_sprite = engine->createSprite("data/bomb.bmp");

    // Create player
    Playership* ship = new PlayerShip(engine, player_ship_sprite, rocket_sprite, screen_res);

    // Creating enemies
    AlienList aliens(engine, alien_sprite, bomb_sprite, screen_res);
    int direction = 1;

    // While game is running
    while (engine->update()) {
        // Print the player score
        char buffer[50];
        sprintf(buffer, "%d", ship->score());
        engine->drawText(30, 30, "Score: ");
        engine->drawText(80, 30, buffer);

        // Print the player health
        buffer[50];
        sprintf(buffer, "%d", ship->health());
        engine->drawText(WIDTH - 140, 30, "Health: ");
        engine->drawText(WIDTH - 80, 30, buffer);

        // Create new enemies if they all are dead
        if (!aliens.has_aliens()) {
            direction = 1;
            aliens.spawn_aliens();
        }

        // Update player
        ship->update();

        // If enemy at border change direction
        if(aliens.alien_out_of_bounds())
            direction = -direction;

        // Update enemy and check all collisions
        aliens.resolve_collisions(ship, direction);

        // If player is dead go to Game Over
        if(ship->health() < 1)
            break;
    }

    // Game Over Screen if player is dead
    while (ship->health() < 1 && engine->update()) {
        char buffer[50];
        sprintf(buffer, "%d", ship->score());
        engine->drawText(WIDTH/2 - 20, HEIGHT/2 - 20, "Game Over!");
        engine->drawText(WIDTH/2 - 20, HEIGHT/2, "Score: ");
        engine->drawText(WIDTH/2 + 30, HEIGHT/2, buffer);
    }

    // Delete player at end of game
    delete ship;

    // Destroy all sprites
    player_ship_sprite->destroy();
    alien_sprite->destroy();
    rocket_sprite->destroy();
    bomb_sprite->destroy();

    // Destroy game engine
    engine->destroy();

    return 0;
}
