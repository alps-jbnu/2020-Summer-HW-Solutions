#pragma once

#include "GameObject.h"

namespace rpg_extreme
{
    class SpikeTrap final : public GameObject
    {
    public:
        SpikeTrap(const int8_t x, const int8_t y);
        virtual char GetSymbol() const override;
    };
}