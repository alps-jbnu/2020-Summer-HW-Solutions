#pragma once

#include "Equipment.h"

namespace rpg_extreme
{
    class Weapon final : public Equipment
    {
    public:
        Weapon(const int16_t attack);
        virtual bool IsArmor() const;
        virtual bool IsAccessory() const;
        virtual bool IsWeapon() const;
        uint16_t GetAttack() const;

    private:
        const uint16_t mAttack;
    };
}