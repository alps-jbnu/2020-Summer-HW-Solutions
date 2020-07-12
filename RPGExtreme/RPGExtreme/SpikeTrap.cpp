#include "SpikeTrap.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    SpikeTrap::SpikeTrap(const int8_t x, const int8_t y)
        : GameObject(x, y)
    {
    }

    char SpikeTrap::GetSymbol() const
    {
        return eSymbolType::SPIKE_TRAP;
    }
    bool SpikeTrap::IsEquipmentGivable() const
    {
        return false;
    }
    bool SpikeTrap::IsAttackable() const
    {
        return false;
    }
    bool SpikeTrap::IsDamageable() const
    {
        return false;
    }
}