#pragma once

#include "Equipment.h"
#include "eAccessoryEffectType.h"

namespace rpg_extreme
{
    class Accessory final : public Equipment
    {
    public:
        Accessory(const eAccessoryEffectType type);
        virtual bool IsArmor() const;
        virtual bool IsAccessory() const;
        virtual bool IsWeapon() const;
        eAccessoryEffectType GetType() const;

    private:
        const eAccessoryEffectType mType;
    };
}