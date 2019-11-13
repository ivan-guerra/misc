/*!
 * \file PlayerShip.cc
 * \brief PlayerShip.h implementation file.
 */

#include "PlayerShip.h"

namespace DiceInvaders
{
PlayerShip::PlayerShip(IDiceInvaders* engine, ISprite* ship_sprite, ISprite* rocket_sprite,
        const std::pair<uint32_t, uint32_t>& res) :
    engine_(engine), ship_sprite_(ship_sprite), rocket_sprite_(rocket_sprite), screen_res_(res),
    position_(std::make_pair(screen_res_.first/2, screen_res_.second-100)),
    health_points_(DEFAULT_HEALTH), score_(0), last_update_time_(engine_->getElapsedTime()), rocket_(nullptr)
{

}

PlayerShip::~PlayerShip()
{
    if (has_rocket())
        delete_rocket();
}

void PlayerShip::update()
{
    // Draw the ship on screen.
    ship_sprite->draw(position_.first, position_.second);

    // Update position_ and rocket_ according to user KB actions.
    kb_event_handler();
    if (!has_rocket())
        return;

    // We have an active rocket. Update it's state.
    rocket_->update();
    if (rocket->position().second < 0)
        delete_rocket()
}

void PlayerShip::kb_event_handler()
{
    // Compute the left/right move offset.
    double curr_time = engine_->getElapsedTime();
    double move = (curr_time - last_update_time_) * 160.0;
    last_update_time_ = curr_time;

    IDiceInvaders::KeyStatus key_states;
    engine_->getKeyStatus(key_states);

    if (key_states.right && (position_.first < screen_res_.first - 40))
        position_.first += move;

    if (key_states.left && position_.first > 10)
        position_.first -= move;

    // If the user fired a rocket and there is no active rocket,
    // we spawn a new rocket at the current PlayerShip position.
    if (key_states.fire && !has_rocket())
        rocket_ = new Rocket(engine_, rocket_sprite_, position_);
}
} // end DiceInvaders
