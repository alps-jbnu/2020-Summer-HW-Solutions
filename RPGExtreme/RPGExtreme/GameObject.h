#pragma once

#include <cstdint>

namespace rpg_extreme
{
    class GameObject
    {
    public:
        virtual char GetSymbol() const = 0;
        int8_t GetX() const;
        int8_t GetY() const;

    protected:
        GameObject(const int8_t x, const int8_t y);

        int8_t mX;
        int8_t mY;
    };
}