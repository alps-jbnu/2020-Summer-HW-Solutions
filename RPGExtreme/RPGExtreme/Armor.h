#pragma once

#include "Equipment.h"

namespace rpg_extreme
{
    class Armor final : public Equipment
    {
    public:
        Armor(const uint16_t defense);

    private:
        const uint16_t mDefense;
    };
}