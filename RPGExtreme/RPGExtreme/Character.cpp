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

    bool Character::IsAlive() const
    {
        return mHp > 0;
    }

    int32_t Character::GetHp() const
    {
        return mHp;
    }

    int32_t Character::GetAttack() const
    {
        return mAttack;
    }

    int32_t Character::GetDefense() const
    {
        return mDefense;
    }

    int32_t Character::GetExp() const
    {
        return mExp;
    }
}