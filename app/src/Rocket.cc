/*!
 * \file Rocket.cc
 * \brief Rocket.h implementation file.
 */

#include "Rocket.h"

namespace DiceInvaders
{
Rocket::Rocket(IDiceInvaders* engine, ISprite* rocket_sprite, const std::pair<uint32_t,uint32_t> position) :
    engine_(engine), rocket_sprite_(rocket_sprite), position_(position), last_update_time_(engine_->getElapsedTime())
{

}

void Rocket::update()
{
    rocket_sprite_->draw(position_.first, position_.second);

    // Compute by how much the the rocket will move up the screen.
    double curr_time = engine_->getElapsedTime();
    double move = (curr_time - last_update_time_) * 360.0;
    last_update_time_ = curr_time;

    position_.second -= move;
}
} // end DiceInvaders
