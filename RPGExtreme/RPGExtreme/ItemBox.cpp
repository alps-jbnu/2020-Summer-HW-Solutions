#include "ItemBox.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    char ItemBox::GetSymbol() const
    {
        return eSymbolType::ITEM_BOX;
    }
}