#include "Monster.h"

namespace rpg_extreme
{
    Monster::Monster(const int8_t x, const int8_t y, const std::string& name, const int16_t attack, const int16_t defense, const int16_t hp, const uint16_t exp)
        : Character(0, 0, 0, 0, 0, 0)
        , mName(name)
    {
    }

    char Monster::GetSymbol() const
    {
        return ' ';
    }

    bool Monster::IsPlayer() const
    {
        return false;
    }

    bool Monster::IsMonster() const
    {
        return false;
    }

    bool Monster::IsAttackable() const
    {
        return false;
    }

    bool Monster::IsAttackedable() const
    {
        return false;
    }

    void Monster::AttackTo(Character* const character)
    {
        Player* player = static_cast<Player*>(character);
    }

    void Monster::OnAttacked(GameObject* const gameObject, const int16_t damage)
    {
        
    }

    const std::string& Monster::GetName() const
    {
        return mName;
    }

    bool Monster::IsBoss() const
    {
        return false;
    }
}