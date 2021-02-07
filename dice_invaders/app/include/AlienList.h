/*!
 * \file AlienList.h
 * \brief Declare a container class for managing a group of Aliens.
 */

#pragma once

#include <utility>
#include <list>
#include "Alien.h"
#include "PlayerShip.h"
#include "DiceInvaders.h"

namespace DiceInvaders
{
/*!
 * \class AlienList
 * \brief A doubly-linked list specifically used to manage Alien objects.
 * \details The concept behind AlienList is to provide and efficient way
 * 			of managing the interaction between Alien and PlayerShip objects in game.
 *			AlienList provides the interface for spawning alien and armies and updating
 *			game state based on collisions between aliens, rockets, players, and the boundaries
 *			of the game window.
 */
class AlienList
{
    public:
        /*!
         * \brief AlienList cannot be default constructed.
         */
        AlienList() = delete;

        AlienList(IDiceInvaders* engine, ISprite* alien_sprite1, ISprite* alien_sprite2,
                ISprite* bomb_sprite, const std::pair<int,int>& screen_res);

        /*!
         * \brief AlienList cannot be copy constructed.
         */
        AlienList(const AlienList& al) = delete;

        /*!
         * \brief AlienList does not support move semantics.
         */
        AlienList(AlienList&& al) = delete;

        /*!
         * \brief AlienList does not allocate resources that aren't automatically managed.
         */
        ~AlienList() = default;

        /*!
         * \brief AlienList does not support assignment.
         */
        AlienList& operator=(const AlienList& al) = delete;

        /*!
         * \brief Resolve collisions if any between \p player and aliens in the AlienList.
         * \details resolve_collisions() traverses the AlienList and for each alien in the list
         * 			it takes actions if
         *			(1) The alien hits the player.
         *			(2) The alien's bomb hits the player.
         *			(3) The player's rocket hits the alien.
         *			The goal is to 'resolve' each of the above collision scenarios by updating player,
         *			alien, and AlienList state accordingly.
         * \param ship A PlayerShip object.
         * \param direction The horizontal direction of the aliens (-1:left and 1:right).
         */
        void resolve_collisions(PlayerShip* ship, int direction);

        /*!
         * \brief Determine whether any alien in AlienList has stepped out of the game bounds.
         * \return True if any alien in AlienList stepped out of bounds.
         */
        bool alien_out_of_bounds() const;

        /*!
         * \brief Spawn an army of aliens.
         * \details spawn_aliens creates #TOTAL_ALIENS Alien objects which are drawn on screen during
         * 			the next game refresh cycle.
         */
        void spawn_aliens();

        /*!
         * \brief Determine whether the AlienList contains any aliens.
         * \return True if the AlienList has at least one alien.
         */
        bool has_aliens() const { return !aliens_.empty(); }

    private:
        static const int TOTAL_ALIENS = 40; /*!< The maximum number of aliens that can be in game simultaneously. */
        static const int ALIENS_PER_ROW = 10; /*!< The number of aliens that appear per row. */

        /*!
         * \brief Determine whether there is a collision between \p pos1 and \p pos2.
         * \return True if \p pos1 and \p pos2 collide.
         */
        bool has_collision(const std::pair<int,int>& pos1, const std::pair<int,int>& pos2) const;

        IDiceInvaders* engine_; /*!< Game driver providing draw and elapsed time functionality. */
        ISprite* alien_sprite1_; /*!< Alien sprite. */
        ISprite* alien_sprite2_; /*!< Alien sprite. */
        ISprite* bomb_sprite_; /*!< Bomb sprite */
        std::pair<int,int> screen_res_; /*!< Game screen resolution. */
        std::list<Alien> aliens_; /*!< List of Alien objects forming the alien army. */
}; // end AlienList

} // end DiceInvaders
