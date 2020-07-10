#pragma once

#include <string>

#include "GameObject.h"

namespace rpg_extreme
{
    class Monster : public GameObject
    {
    public:
        virtual char GetSymbol() const override;

    protected:
        std::string mName;
    };
}