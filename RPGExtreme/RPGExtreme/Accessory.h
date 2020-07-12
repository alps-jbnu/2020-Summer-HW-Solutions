#pragma once

#include "Equipment.h"
#include "eAccessoryType.h"

namespace rpg_extreme
{
    class Accessory final : public Equipment
    {
    public:
        Accessory(const eAccessoryType type);
        virtual bool IsArmor() const;
        virtual bool IsAccessory() const;
        virtual bool IsWeapon() const;
        eAccessoryType GetType() const;

    private:
        const eAccessoryType mType;
    };
}