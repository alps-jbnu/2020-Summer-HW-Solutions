#pragma once

#include "Monster.h"

namespace rpg_extreme
{
    class BossMonster final : public Monster
    {
    public:
        BossMonster(const int8_t x, const int8_t y, const std::string& name, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp);
        virtual char GetSymbol() const override;
    };
}