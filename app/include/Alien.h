/*!
 * \file Alien.h
 * \brief Declare a type to represent alien invaders.
 */

#pragma once

#include <cstdint>
#include <utility>
#include "Bomb.h"

namespace DiceInvaders
{
/*!
 * \class Alien
 * \brief Represent an alien invader.
 * \details Alien is an object that exposes the interface needed to draw
 *			an alien sprite in different locations over the object's
 *			lifetime. Alien objects also periodically drop bombs and
 * 			for drawing/managing the bomb over its lifetime.
 */
class Alien
{
public:
    /*!
     * \brief Alien cannot be default constructed.
     */
    Alien() = delete;

    Alien(IDiceInvaders* engine, ISprite* alien_sprite, ISprite* bomb_sprite,
            uint32_t hpos, uint32_t vpos, const std::pair<uint32_t,uint32_t>& screen_res);

    /*!
     * \brief Alien does not support copy construction.
     */
    Alien(const ALien& a) = delete;

    /*!
     * \brief Alien does not support move semantics.
     */
    Alien(Alien&& a) = delete;

    /*!
     * \brief Clean up resources consumed by this Alien.
     * \details Worth noting that even though Alien works with many different
     *			pointer types, Alien objects will only destruct those objects which
     *			are allocated during the lifetime of the object.
     */
    ~Alien();

    /*!
     * \brief Alien does not support assignment.
     */
    Alien& operator=(const Alien& a) = delete;

    /*!
     * \brief Determine whether this Alien instance has an active bomb.
     * \return True if this Alien instance has an active bomb.
     */
    bool has_bomb() const { return (nullptr != bomb_); }

    /*!
     * \brief Delete the active bomb if any.
     */
    void delete_bomb() { delete bomb_; }

    /*!
     * \brief Get the position of the alien in 2D space.
     * \return The position of the alien in 2D space.
     */
    std::pair<uint32_t,uint32_t> position() const { return position_; }

    /*!
     * \brief Get the position of this alien's bomb in 2D space.
     * \return The position of this alien's bomb in 2D space.
     */
    std::pair<uint32_t,uint32_t> bomb_position() const { return (bomb_) ? bomb_->position() : std::make_pair(0,0); }

    /*!
     * \brief Determine whether the alien has beyond the bounds of the screen.
     * \return True if the alien has moved beyond the left or right bound of the screen.
     */
    bool out_of_bounds() const { return ((position.first > (screen_res_.first - 30.0)) || (position.first < 0)); }

    /*!
     * \brief Update the state of the Alien in game.
     * \param direction A directional flag. -1 indicates left and 1 indicates right.
     */
    void update(int direction);

private:
    IDiceInvaders* engine_; /*!< Game driver providing draw and elapsed time functionality. */
    ISprite* alien_sprite_; /*!< Alien sprite. */
    ISprite* bomb_sprite_; /*!< Bomb sprite. */
    std::pair<uint32_t,uint32_t> position_; /*!< Alien position in 2D space. */
    std::pair<uint32_t,uint32_t> screen_res_; /*!< Game screen resolution. */

    int prev_dir_; /*!< Record of the alien's horizontal direction (left/right). */
    int bomb_trigger_; /*!< Random integer used to decide when this alien will drop a bomb. */
    double last_update_time_; /*!< Record of the game time during the last call to update(). */
    double last_bomb_time_; /*!< Record of the game time during which the last bomb was dropped. */
    Bomb* bomb_; /*!< Pointer to this alien's bomb object. */
}; // end Alien

}; // end DiceInvaders
