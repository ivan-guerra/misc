/*!
 * \file AlienList.cc
 * \brief AlienList.h implementation file.
 */

#include "AlienList.h"

namespace DiceInvaders
{
AlienList::AlienList(IDiceInvaders* engine, ISprite* alien_sprite1, ISprite* alien_sprite2,
        ISprite* bomb_sprite, const std::pair<int,int>& screen_res) :
    engine_(engine), alien_sprite1_(alien_sprite1), alien_sprite2_(alien_sprite2),
    bomb_sprite_(bomb_sprite), screen_res_(screen_res)
{

}

void AlienList::resolve_collisions(PlayerShip* ship, int direction)
{
    for (auto i = aliens_.begin(); i != aliens_.end();) {
        i->update(direction);

        if (i->position().second > 440) {
            ship->health(0);
            break;
        } else if (ship->has_rocket() && has_collision(i->position(), ship->rocket_position())) {
            // A rocket hit the alien.
            ship->delete_rocket();
            ship->score(ship->score()+10);
            i = aliens_.erase(i);
        } else if (has_collision(ship->position(), i->position())) {
            // An alien hit the ship's ship.
            ship->health(ship->health()-1);
            i = aliens_.erase(i);
        } else if (i->has_bomb() && has_collision(i->bomb_position(), ship->position())) {
            // An alien bomb hit the ship's ship.
            ship->health(ship->health()-1);
            i->delete_bomb();
        } else {
            ++i;
        }
    }
}

bool AlienList::alien_out_of_bounds() const
{
    for (const auto& a : aliens_) {
        if (a.out_of_bounds())
            return true;
    }
    return false;
}

void AlienList::spawn_aliens()
{
    for (unsigned int i = 0; i < TOTAL_ALIENS; ++i) {
        ISprite* alien_sprite = (i % 2 == 0) ? alien_sprite1_ : alien_sprite2_;
        Alien alien(engine_, alien_sprite, bomb_sprite_, i % ALIENS_PER_ROW, i / ALIENS_PER_ROW, screen_res_);
        aliens_.push_back(alien);
    }
}

bool AlienList::has_collision(const std::pair<int,int>& pos1, const std::pair<int,int>& pos2) const
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
