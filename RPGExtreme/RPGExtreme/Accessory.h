#pragma once

#include "Equipment.h"
#include "eAccessoryType.h"

namespace rpg_extreme
{
    class Accessory final : public Equipment
    {
    public:
        Accessory(const eAccessoryType type);

    private:
        const eAccessoryType mType;
    };
}