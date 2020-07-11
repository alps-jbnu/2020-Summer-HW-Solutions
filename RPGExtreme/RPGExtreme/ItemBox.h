#pragma once

#include <cstdint>

#include "GameObject.h"
#include "Equipment.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    class ItemBox final : public GameObject
    {
    public:
        ItemBox(const int8_t x, const int8_t y, const Equipment& equipment);
        virtual char GetSymbol() const override;

    private:
        Equipment mEquipment;
    };
}