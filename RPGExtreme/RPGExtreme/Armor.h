#pragma once

#include "Equipment.h"

namespace rpg_extreme
{
    class Armor final : public Equipment
    {
    public:
        Armor(const int16_t defense);

        virtual bool IsArmor() const;
        virtual bool IsAccessory() const;
        virtual bool IsWeapon() const;
        int16_t GetDefense() const;

    private:
        const int16_t mDefense;
    };
}