#include "Character.h"

namespace rpg_extreme
{
    Character::Character(const int8_t x, const int8_t y, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp)
        : GameObject(x, y)
        , mAttack(attack)
        , mDefense(defense)
        , mHp(hp)
        , mExp(exp)
    {
    }
}