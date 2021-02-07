/*!
 * \file PlayerShip.h
 * \brief Declare a type for representing the player's space ship.
 */

#pragma once

#include <cstdint>
#include <utility>
#include "Rocket.h"
#include "DiceInvaders.h"

namespace DiceInvaders
{
/*!
 * \class PlayerShip
 * \brief Represent the player's space ship.
 * \details PlayerShip is an object that exposes the interface needed to draw
 *			a space ship sprite in different locations over the object's
 *			lifetime. PlayerShip objects also process keyboard events
 *          which include left/right movement of the ship as well as
 *          firing of a rocket.
 */
class PlayerShip
{
public:
    /*!
     * \brief PlayerShip cannot be default constructed.
     */
    PlayerShip() = delete;

    PlayerShip(IDiceInvaders* engine, ISprite* ship_sprite,
            ISprite* rocket_sprite, const std::pair<float, float>& res);

    /*!
     * \brief PlayerShip does not support copy construction.
     */
    PlayerShip(const PlayerShip& ps) = delete;

    /*!
     * \brief PlayerShip does not support move semantics.
     */
    PlayerShip(PlayerShip&& ps) = delete;

    /*!
     * \brief Clean up resources consumed by this PlayerShip.
     * \details PlayerShip will only destruct those items it directly allocates
     *			during its lifetime.
     */
    ~PlayerShip();

    /*!
     * \brief PlayerShip does not support assignment.
     */
    PlayerShip& operator=(const PlayerShip ps) = delete;

    /*!
     * \brief Set the health points of this PlayerShip.
     * \param hp This PlayerShip's health points.
     */
    void health(int hp) { health_points_ = hp; }

    /*!
     * \brief Get this PlayerShip's health points.
     * \return This PlayerShip's health points.
     */
    int health() const { return health_points_; }

    /*!
     * \brief Set this PlayerShip's score.
     * \param score The PlayerShip's new score.
     */
    void score(int score) { score_ = score; }

    /*!
     * \brief Get this PlayerShip's score.
     * \return This PlayerShip's score.
     */
    int score() const { return score_; }

    /*!
     * \brief The position of this PlayerShip in 2D space.
     * \return The position of this PlayerShip in 2D space.
     */
    std::pair<int,int> position() const { return position_; }

    /*!
     * \brief The position of this PlayerShip's active rocket in 2D space.
     * \return The position of this PlayerShip's active rocket in 2D space. If
     *		   this PlayerShip has not fired a rocket, (0,0) is returned.
     */
    std::pair<float,float> rocket_position() const { return (rocket_) ? rocket_->position() : std::make_pair(0.0f,0.0f); }

    /*!
     * \brief Determine whether this PlayerShip has an active rocket.
     * \return True if the PlayerShip has fired a rocket that is still active.
     */
    bool has_rocket() const { return (nullptr != rocket_); }

    /*!
     * \brief Delete this PlayerShip's active rocket.
     */
    void delete_rocket() { delete rocket_; rocket_ = nullptr; }

    /*!
     * \brief Update the state of the PlayerShip in game.
     * \details update() will draw the ship in a location corresponding
     *			to the user's last move keystrokes. Additionally, update()
     *			will manage the update of this PlayerShip's rocket if any.
     */
    void update();

private:
    /*!
     * \brief Use player keystrokes to update the state of the PlayerShip.
     * \details kb_event_handler() will update the PlayerShip position according
     *   		to the user's left/right keystrokes. Additionally, if the player
     *          'fires', kb_event_handler() will spawn a rocket object.
     */
    void kb_event_handler();

    const static int DEFAULT_HEALTH = 3; /*!< Default PlayerShip health. */

    IDiceInvaders* engine_; /*!< Game driver providing draw and elapsed time functionality. */
    ISprite* ship_sprite_; /*!< Ship sprite */
    ISprite* rocket_sprite_; /*!< Rocket sprite. */
    std::pair<int,int> screen_res_; /*!< Game screen resolution. */
    std::pair<float,float> position_; /*!< PlayerShip position in 2D space. */
    int health_points_; /*!< PlayerShip health points. */
    int score_; /*!< PlayerShip score representing number of aliens shot down. */
    float last_update_time_; /*!< Record of the game time during the last call to update(). */
    Rocket* rocket_; /*!< Pointer to this PlayerShip's active rocket. */
}; // end PlayerShip

} // end DiceInvaders
