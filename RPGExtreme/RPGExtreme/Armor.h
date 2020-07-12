#pragma once

#include "Equipment.h"

namespace rpg_extreme
{
    class Armor final : public Equipment
    {
    public:
        Armor(const uint16_t defense);
        virtual bool IsArmor() const;
        virtual bool IsAccessory() const;
        virtual bool IsWeapon() const;
        uint16_t GetDefense() const;

    private:
        const uint16_t mDefense;
    };
}