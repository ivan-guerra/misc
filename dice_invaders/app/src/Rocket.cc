/*!
 * \file Rocket.cc
 * \brief Rocket.h implementation file.
 */

#include "Rocket.h"

namespace DiceInvaders
{
Rocket::Rocket(IDiceInvaders* engine, ISprite* rocket_sprite, const std::pair<float,float> position) :
    engine_(engine), rocket_sprite_(rocket_sprite),
    position_(position), last_update_time_(engine_->getElapsedTime())
{

}

void Rocket::update()
{
    rocket_sprite_->draw(position_.first, position_.second);

    // Compute by how much the the rocket will move up the screen.
    float curr_time = engine_->getElapsedTime();
    float move = (curr_time - last_update_time_) * 160.0f;
    last_update_time_ = curr_time;

    position_.second -= move;
}
} // end DiceInvaders
