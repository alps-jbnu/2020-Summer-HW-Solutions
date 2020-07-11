#include "Monster.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    Monster::Monster(const int8_t x, const int8_t y, const std::string& name, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp)
        : Character(x, y, attack, defense, hp, exp)
        , mName(name)
    {
    }

    char Monster::GetSymbol() const
    {
        return eSymbolType::MONSTER;
    }

    const std::string& Monster::GetName() const
    {
        return mName;
    }
}