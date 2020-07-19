#include "BossMonster.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    BossMonster::BossMonster(const int8_t x, const int8_t y, const std::string& name, const int16_t attack, const int16_t defense, const int16_t hp, const int16_t exp)
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