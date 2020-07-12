#pragma once

#include <cstdint>

#include "GameObject.h"
#include "Equipment.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    class EquipmentBox final : public GameObject
    {
    public:
        EquipmentBox(const int8_t x, const int8_t y, Equipment* equipment);
        virtual ~EquipmentBox();

        virtual bool IsEquipmentGivable() const override;
        virtual bool IsAttackable() const override;
        virtual bool IsDamageable() const override;
        virtual char GetSymbol() const override;
        Equipment* GetEquipment() const;
        void Clear();

    private:
        Equipment* mEquipment;
    };
}