#pragma once

#include "GameObject.h"

namespace rpg_extreme
{
    class Character : public GameObject
    {
    public:
        bool IsAlive() const;
        virtual void AttackTo(Character& character) = 0;
        virtual void OnAttack(const int16_t damage) = 0;

        int32_t GetHp() const;
        int32_t GetAttack() const;
        int32_t GetDefense() const;
        int32_t GetExp() const;

    protected:
        Character(const int8_t x, const int8_t y, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp);

        int32_t mHp;
        int32_t mAttack;
        int32_t mDefense;
        int32_t mExp;
    };
}