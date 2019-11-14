/*!
 * \file Bomb.cc
 * \brief Bomb.h implementation file.
 */

#include "Bomb.h"

namespace DiceInvaders
{
Bomb::Bomb(IDiceInvaders* engine, ISprite* bomb_sprite, const std::pair<float,float>& position) :
    engine_(engine), bomb_sprite_(bomb_sprite),
    position_(position), last_update_time_(engine_->getElapsedTime())
{

}

void Bomb::update()
{
    bomb_sprite_->draw(position_.first, position_.second);

    // Compute by how much the the rocket will move down the screen.
    float curr_time = engine_->getElapsedTime();
    float move = (curr_time - last_update_time_) * 160.0f;
    last_update_time_ = curr_time;

    position_.second += move;
}

} // end DiceInvaders
