#pragma once

#include <cstdint>

#include "Character.h"

namespace rpg_extreme
{
    class Player final : public Character
    {
    public:
        Player(const int8_t x, const int8_t y);

        virtual char GetSymbol() const override;
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveTo(const int8_t x, const int8_t y);

    private:
        int32_t mMaxHp;
        int32_t mLevel;
    };
}