#pragma once

#include "Equipment.h"

namespace rpg_extreme
{
    class Weapon final : public Equipment
    {
    public:
        Weapon(const uint16_t attack);

    private:
        const uint16_t mAttack;
    };
}