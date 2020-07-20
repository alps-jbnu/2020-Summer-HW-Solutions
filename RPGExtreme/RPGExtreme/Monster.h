#pragma once

#include <string>

#include "Character.h"
#include "IAttackable.h"
#include "IAttackedable.h"

namespace rpg_extreme
{
    class Monster : public Character, public IAttackable, public IAttackedable
    {
    public:
        Monster(const int8_t x, const int8_t y, const std::string& name, const int16_t attack, const int16_t defense, const int16_t hp, const int16_t exp);
        
        virtual char GetSymbol() const override;
        virtual bool IsPlayer() const override;
        virtual bool IsMonster() const override;

        virtual bool IsAttackable() const;
        virtual bool IsAttackedable() const;
        virtual void AttackTo(Character* character);
        virtual void OnAttack(GameObject* gameObject, const int16_t damage);

        const std::string& GetName() const;
        virtual bool IsBoss() const;

    protected:
        std::string mName;
    };
}