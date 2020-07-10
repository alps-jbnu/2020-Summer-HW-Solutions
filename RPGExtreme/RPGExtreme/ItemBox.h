#pragma once

#include "GameObject.h"

namespace rpg_extreme
{
    class ItemBox final : public GameObject
    {
    public:
        virtual char GetSymbol() const override;
    };
}