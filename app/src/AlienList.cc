/*!
 * \file AlienList.cc
 * \brief AlienList.h implementation file.
 */

#include "AlienList.h"

namespace DiceInvaders
{
AlienList::AlienList(IDiceInvaders* engine, ISprite* alien_sprite, ISPrite* bomb_sprite, const std::pair<uint32_t,uint32_t>& screen_res) :
    engine_(engine), alien_sprite_(alien_sprite), bomb_sprite_(bomb_sprite), screen_res_(screen_res)
{

}

void AlienList::resolve_collisions(PlayerShip* player, int direction)
{
    for (auto i = aliens_.begin(); i != aliens_.end();) {
        i->update(direction);

        if (i->position.second > 440) {
            player->health(0);
        } else if (player->has_rocket() && has_collision(i->position(), player->rocket_position())) {
            // A rocket hit the alien.
            player->delete_rocket();
            player->score(10);
            i = aliens_.erase(i);
        } else if (has_collision(player->position(), i->position())) {
            // An alien hit the player's ship.
            player->health(player->health()-1);
            i = aliens_.erase(i);
        } else if (i->has_bomb() && has_collision(i->bomb_position(), player->position())) {
            // An alien bomb hit the player's ship.
            player->health(player->health()-1);
            i->delete_bomb();
        } else {
            ++i;
        }
    }
}

bool AlienList::alien_out_of_bounds() const
{
    for (const auto& a : aliens_) {
        if (a->out_of_bounds())
            return true;
    }
    return false;
}

void AlienList::spawn_aliens()
{
    for (int i = 0; i < TOTAL_ALIENS; ++i)
        aliens_.emplace_back((engine_, alien_sprite_, bomb_sprite_, i%ALIENS_PER_ROW, i/ALIENS_PER_ROW, screen_res_));
}

bool AlienList::has_collision(const std::pair<uint32_t,uint32_t>& pos1, const std::pair<uint32_t,uint32_t>& pos2) const
{
    if (pos2.first > pos1.first - 15 &&
            pos2.first < pos1.first + 15 &&
            pos2.second > pos1.second - 15 &&
            pos2.second < pos1.second + 15) {
        return true;
    }
    return false;
}
} // end DiceInvaders
