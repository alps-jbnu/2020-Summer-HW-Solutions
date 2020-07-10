#pragma once

#include <cstdint>

namespace rpg_extreme
{
    class GameObject
    {
    public:
        virtual char GetSymbol() const;

    protected:
        int8_t mX;
        int8_t mY;
    };
}