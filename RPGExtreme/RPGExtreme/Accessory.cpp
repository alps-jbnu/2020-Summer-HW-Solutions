#include "Accessory.h"

namespace rpg_extreme
{
    Accessory::Accessory(const eAccessoryType type)
        : mType(type)
    {
    }

    bool Accessory::IsArmor() const
    {
        return false;
    }

    bool Accessory::IsAccessory() const
    {
        return true;
    }

    bool Accessory::IsWeapon() const
    {
        return false;
    }
    eAccessoryType Accessory::GetType() const
    {
        return mType;
    }
}