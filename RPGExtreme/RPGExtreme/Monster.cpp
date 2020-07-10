#include "Monster.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    char Monster::GetSymbol() const
    {
        return eSymbolType::MONSTER;
    }
}