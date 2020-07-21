#include "Weapon.h"

namespace rpg_extreme
{
    Weapon::Weapon(const int16_t attack)
        : Equipment()
        , mAttack(attack)
    {
    }

    bool Weapon::IsArmor() const
    {
        return false;
    }

    bool Weapon::IsAccessory() const
    {
        return false;
    }

    bool Weapon::IsWeapon() const
    {
        return true;
    }

    uint16_t Weapon::GetAttack() const
    {
        return mAttack;
    }
}