/*!
 * \file Rocket.h
 * \brief Declare a type to represent player ship rockets.
 */

#pragma once

#include <utility>
#include "DiceInvaders.h"

namespace DiceInvaders
{
/*!
 * \class Rocket
 * \brief Represent a rocket fired by the player's ship.
 */
class Rocket
{
public:
    /*!
     * \brief Rocket cannot be default constructed.
     */
    Rocket() = delete;

    Rocket(IDiceInvaders* engine, ISprite* rocket_sprite, const std::pair<float,float> position);

    /*!
     * \brief Rocket cannot be copy constructed.
     */
    Rocket(const Rocket& r) = delete;

    /*!
     * \brief Rocket does not support move semantics.
     */
    Rocket(Rocket&& r) = delete;

    /*!
     * \brief Default destructor.
     * \details Rocket works with many different pointers but does not allocate any
     * 			memory of its own.
     */
    ~Rocket() = default;

    /*!
     * \brief Rocket does not support assignment.
     */
    Rocket& operator=(const Rocket& r) = delete;

    /*!
     * \brief Get the position of the rocket in 2D space.
     * \return The position of the rocket in 2D space.
     */
    std::pair<float,float> position() const { return position_; }

    /*!
     * \brief Update the position of the rocket on screen.
     */
    void update();

private:
    IDiceInvaders* engine_; /*!< Game driver providing draw and elapsed time functionality. */
    ISprite* rocket_sprite_; /*!< Rocket sprite. */
    std::pair<float,float> position_; /*!< Rocket position in 2D space. */
    float last_update_time_; /*!< Record of the game time during the last call to update(). */
}; // end Rocket

} // end DiceInvaders
