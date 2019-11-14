/*!
 * \file Alien.h
 * \brief Declare a type to represent alien invaders.
 */

#pragma once

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
            int hpos, int vpos, const std::pair<int,int>& screen_res);

    Alien(const Alien& a) = default;

    Alien(Alien&& a) = default;

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
    void delete_bomb() { delete bomb_; bomb_ = nullptr; }

    /*!
     * \brief Get the position of the alien in 2D space.
     * \return The position of the alien in 2D space.
     */
    std::pair<float,float> position() const { return position_; }

    /*!
     * \brief Get the position of this alien's bomb in 2D space.
     * \return The position of this alien's bomb in 2D space.
     */
    std::pair<float,float> bomb_position() const { return (bomb_) ? bomb_->position() : std::make_pair(0.0f,0.0f); }

    /*!
     * \brief Determine whether the alien has beyond the bounds of the screen.
     * \return True if the alien has moved beyond the left or right bound of the screen.
     */
    bool out_of_bounds() const { return ((position_.first > (screen_res_.first - 30.0)) || (position_.first < 0)); }

    /*!
     * \brief Update the state of the Alien in game.
     * \param direction A directional flag. -1 indicates left and 1 indicates right.
     */
    void update(int direction);

private:
    IDiceInvaders* engine_; /*!< Game driver providing draw and elapsed time functionality. */
    ISprite* alien_sprite_; /*!< Alien sprite. */
    ISprite* bomb_sprite_; /*!< Bomb sprite. */
    std::pair<float,float> position_; /*!< Alien position in 2D space. */
    std::pair<int,int> screen_res_; /*!< Game screen resolution. */

    int prev_dir_; /*!< Record of the alien's horizontal direction (left/right). */
    int bomb_trigger_; /*!< Random integer used to decide when this alien will drop a bomb. */
    float last_update_time_; /*!< Record of the game time during the last call to update(). */
    float last_bomb_time_; /*!< Record of the game time during which the last bomb was dropped. */
    Bomb* bomb_; /*!< Pointer to this alien's bomb object. */
}; // end Alien

}; // end DiceInvaders
