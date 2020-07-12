#include "Monster.h"
#include "eSymbolType.h"
#include "Player.h"

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

    bool Monster::IsEquipmentGivable() const
    {
        return false;
    }

    bool Monster::IsAttackable() const
    {
        return true;
    }

    bool Monster::IsDamageable() const
    {
        return true;
    }

    void Monster::AttackTo(Character& character)
    {
        auto& player = static_cast<Player&>(character);
        int32_t damage = mAttack - (player.GetDefense() + player.GetBonusDefense());
        if (damage <= 0)
        {
            damage = 1;
        }
        character.OnAttack(damage);
    }

    void Monster::OnAttack(const int16_t damage)
    {
        mHp -= damage;
        if (mHp <= 0)
        {
            mHp = 0;
        }
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