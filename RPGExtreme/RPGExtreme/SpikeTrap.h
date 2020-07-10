#pragma once

#include "GameObject.h"

namespace rpg_extreme
{
    class SpikeTrap final : public GameObject
    {
    public:
        virtual char GetSymbol() const override;
    };
}