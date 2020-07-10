#pragma once

#include "Monster.h"

namespace rpg_extreme
{
    class BossMonster final : public Monster
    {
    public:
        virtual char GetSymbol() const override;
    };
}