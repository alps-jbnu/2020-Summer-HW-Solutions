#include "SpikeTrap.h"

namespace rpg_extreme
{
    SpikeTrap::SpikeTrap(const int8_t x, const int8_t y)
        : GameObject(x, y)
    {
    }

    char SpikeTrap::GetSymbol() const
    {
        return ' ';
    }

    bool SpikeTrap::IsCharacter() const
    {
        return false;
    }

    bool SpikeTrap::IsEquipmentBox() const
    {
        return false;
    }
    
    bool SpikeTrap::IsWall() const
    {
        return false;
    }

    bool SpikeTrap::IsSpikeTrap() const
    {
        return false;
    }

    bool SpikeTrap::IsAttackable() const
    {
        return false;
    }

    void SpikeTrap::AttackTo(Character* const character)
    {
        Player* player = static_cast<Player*>(character);
    }
}