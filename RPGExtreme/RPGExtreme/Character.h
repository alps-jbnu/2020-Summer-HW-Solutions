#pragma once

#include "GameObject.h"

namespace rpg_extreme
{
    class Character : public GameObject
    {
    protected:
        Character(const int8_t x, const int8_t y, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp);

        int32_t mHp;
        int32_t mAttack;
        int32_t mDefense;
        int32_t mExp;
    };
}