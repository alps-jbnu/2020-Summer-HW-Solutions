#pragma once

#include <cstdint>

#include "GameObject.h"

namespace rpg_extreme
{
    class Player final : public GameObject
    {
    public:
        virtual char GetSymbol() const override;
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

    private:
        int32_t mMaxHp;
        int32_t mHp;
        int32_t mAttack;
        int32_t mDefense;
        int32_t mExp;
        int32_t mLevel;

    };
}