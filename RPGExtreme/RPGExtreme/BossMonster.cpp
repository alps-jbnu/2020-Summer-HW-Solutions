#include "BossMonster.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    char BossMonster::GetSymbol() const
    {
        return eSymbolType::BOSS_MONSTER;
    }
}