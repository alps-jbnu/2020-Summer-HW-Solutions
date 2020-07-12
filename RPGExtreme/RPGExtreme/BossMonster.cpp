#include "BossMonster.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    BossMonster::BossMonster(const int8_t x, const int8_t y, const std::string& name, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp)
        : Monster(x, y, name, attack, defense, hp, exp)
    {
    }

    char BossMonster::GetSymbol() const
    {
        return eSymbolType::BOSS_MONSTER;
    }

    bool BossMonster::IsBoss() const
    {
        return true;
    }
}