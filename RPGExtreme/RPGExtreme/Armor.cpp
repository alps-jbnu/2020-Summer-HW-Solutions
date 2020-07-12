#include "Armor.h"

namespace rpg_extreme
{
    Armor::Armor(const uint16_t defense)
        : mDefense(defense)
    {
    }

    bool Armor::IsArmor() const
    {
        return true;
    }

    bool Armor::IsAccessory() const
    {
        return false;
    }

    bool Armor::IsWeapon() const
    {
        return false;
    }
    
    uint16_t Armor::GetDefense() const
    {
        return mDefense;
    }
}