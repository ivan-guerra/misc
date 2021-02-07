/*!
 * \file Alien.cc
 * \brief Alien.h implementation file.
 */

#include <cstdlib>
#include "Alien.h"

namespace DiceInvaders
{
Alien::Alien(IDiceInvaders* engine, ISprite* alien_sprite, ISprite* bomb_sprite,
        int hpos, int vpos, const std::pair<int,int>& screen_res) :
    engine_(engine), alien_sprite_(alien_sprite), bomb_sprite_(bomb_sprite),
    position_(std::make_pair(hpos*40+15, vpos*40+55)), screen_res_(screen_res),
    prev_dir_(1), bomb_trigger_(rand() % 30 + 1), last_update_time_(engine_->getElapsedTime()),
    last_bomb_time_(engine_->getElapsedTime()), bomb_(nullptr)
{

}

Alien::~Alien()
{
    if (has_bomb())
        delete_bomb();
}

void Alien::update(int direction)
{
    alien_sprite_->draw(position_.first, position_.second);

    // Compute the alien's left/right move offset.
    float curr_time = engine_->getElapsedTime();
    float move = (curr_time - last_update_time_) * 160.0f;
    last_update_time_ = curr_time;

    // If we changed direction since the last update,
    // we have to update the alien move down and horizontally.
    if (prev_dir_ != direction) {
        if (direction > 0)
            position_.first += 5;
        else
            position_.first -= 5;

        position_.second += 15;
        prev_dir_ = direction;
    }

    position_.first += direction * move;

    // Launch a bomb randomly.
    if (!has_bomb() && ((curr_time - last_bomb_time_) + bomb_trigger_) > 30) {
        bomb_trigger_ = rand() % 30 + 1;
        last_bomb_time_ = curr_time;
        bomb_ = new Bomb(engine_, bomb_sprite_, position_);
    }

    // Update an existing bomb.
    if (has_bomb()) {
        bomb_->update();
        if (bomb_->position().second > screen_res_.second)
            delete_bomb();
    }
}
} // end DiceInvaders
