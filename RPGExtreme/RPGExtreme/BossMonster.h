#pragma once

#include "Monster.h"

namespace rpg_extreme
{
    class BossMonster final : public Monster
    {
    public:
        BossMonster(const int8_t x, const int8_t y, const std::string& name, const int16_t attack, const int16_t defense, const int16_t hp, const int16_t exp);
        virtual char GetSymbol() const;
        virtual bool IsBoss() const;
    };
}