#include "ItemBox.h"

namespace rpg_extreme
{
    ItemBox::ItemBox(const int8_t x, const int8_t y, const Equipment& equipment)
        : GameObject(x, y)
        , mEquipment(equipment)
    {
    }

    char ItemBox::GetSymbol() const
    {
        return eSymbolType::ITEM_BOX;
    }
}