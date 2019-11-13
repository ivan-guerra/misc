/*!
 * \file Bomb.h
 * \brief Declare a type to represent alien bombs.
 */

#pragma once

#include <cstdint>
#include <utility>
#include "DiceInvaders.h"

namespace DiceInvaders
{
/*!
* \class Bomb
* \brief Represent a bomb dropped by the alien.
*/
class Bomb
{
public:
    /*!
     * \brief Bomb cannot be default constructed.
     */
    Bomb() = delete;

    Bomb(IDiceInvaders* engine, ISprite* bomb_sprite, const std::pair<uint32_t,uint32_t>& position);

    /*!
     * \brief Bomb cannot be copy constructed.
     */
    Bomb(const Bomb& b) = delete;

    /*!
     * \brief Bomb does not support move semantics.
     */
    Bomb(Bomb&& b) = delete;

    /*!
     * \brief Default destructor.
     * \details Bomb works with many different pointers but does not allocate any
     * 			memory of its own.
     */
    ~Bomb() = default;

    /*!
     * \brief Bomb does not support assignment.
     */
    Bomb& operator=(const Bomb& b) = delete;

    /*!
     * \brief Get the position of the bomb in 2D space.
     * \return The position of the bomb in 2D space.
     */
    std::pair<uint32_t,uint32_t> position() const { return position_; }

    /*!
     * \brief Update the position of the bomb on screen.
     */
    void update();

private:
    IDiceInvaders* engine_; /*!< Game driver providing draw and elapsed time functionality. */
    ISprite* bomb_sprite_; /*!< Bomb sprite. */
    std::pair<uint32_t,uint32_t> position_; /*!< Bomb position in 2D space. */
    double last_update_time_; /*!< Record of the game time during the last call to update(). */
}; // end Bomb

} // end DiceInvaders
