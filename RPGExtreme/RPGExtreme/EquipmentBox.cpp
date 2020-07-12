#include "EquipmentBox.h"

namespace rpg_extreme
{
    EquipmentBox::EquipmentBox(const int8_t x, const int8_t y, Equipment* equipment)
        : GameObject(x, y)
        , mEquipment(equipment)
    {
    }

    EquipmentBox::~EquipmentBox()
    {
        delete mEquipment;
    }

    bool EquipmentBox::IsEquipmentGivable() const
    {
        return true;
    }

    bool EquipmentBox::IsAttackable() const
    {
        return false;
    }

    bool EquipmentBox::IsDamageable() const
    {
        return false;
    }

    char EquipmentBox::GetSymbol() const
    {
        return eSymbolType::ITEM_BOX;
    }

    Equipment* EquipmentBox::GetEquipment() const
    {
        return mEquipment;
    }

    void EquipmentBox::Clear()
    {
        mEquipment = nullptr;
    }
}