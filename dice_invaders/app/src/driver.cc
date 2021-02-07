#include <cassert>
#include <cstdio>
#include <cstdint>
#include <utility>
#include <windows.h>

#include "Alien.h"
#include "AlienList.h"
#include "Playership.h"
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"

const int WIDTH = 640;
const int HEIGHT = 480;

using namespace DiceInvaders;

int APIENTRY WinMain(
        HINSTANCE instance,
        HINSTANCE previousInstance,
        LPSTR commandLine,
        int commandShow)
{
    // Create engine.
    DiceInvadersLib lib("../lib/DiceInvaders.dll");
    IDiceInvaders* engine = lib.get();

    // Initialize the window.
    std::pair<uint32_t,uint32_t> screen_res(WIDTH, HEIGHT);
    engine->init(screen_res.first, screen_res.second);

    // Create all sprites.
    ISprite* player_ship_sprite = engine->createSprite("../data/player.bmp");
    ISprite* alien_sprite1 = engine->createSprite("../data/enemy1.bmp");
    ISprite* alien_sprite2 = engine->createSprite("../data/enemy2.bmp");
    ISprite* rocket_sprite = engine->createSprite("../data/rocket.bmp");
    ISprite* bomb_sprite = engine->createSprite("../data/bomb.bmp");

    // Create player ship.
    PlayerShip* ship = new PlayerShip(engine, player_ship_sprite, rocket_sprite, screen_res);

    // Create a list for storing aliens.
    AlienList aliens(engine, alien_sprite1, alien_sprite2, bomb_sprite, screen_res);
    int direction = 1;

    // Launch the game loop.
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

        // Create more aliens if all are dead.
        if (!aliens.has_aliens()) {
            direction = 1;
            aliens.spawn_aliens();
        }

        // Update player.
        ship->update();

        // If an alien has hit the border, change the alien direction.
        if(aliens.alien_out_of_bounds())
            direction = -direction;

        // Update aliens and resolve any possible collisions.
        aliens.resolve_collisions(ship, direction);

        // Ship's dead show the game over screen.
        if(ship->health() < 1)
            break;
    }

    // Diplay a game over screen with the player's score.
    while (ship->health() < 1 && engine->update()) {
        char buffer[50];
        sprintf(buffer, "%d", ship->score());
        engine->drawText(WIDTH/2 - 20, HEIGHT/2 - 20, "Game Over!");
        engine->drawText(WIDTH/2 - 20, HEIGHT/2, "Score: ");
        engine->drawText(WIDTH/2 + 30, HEIGHT/2, buffer);
    }

    // Release all active resources.
    delete ship;
    player_ship_sprite->destroy();
    alien_sprite1->destroy();
    alien_sprite2->destroy();
    rocket_sprite->destroy();
    bomb_sprite->destroy();
    engine->destroy();

    return 0;
}
