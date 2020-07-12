#pragma once

#include <cstdint>
#include <vector>

#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"

namespace rpg_extreme
{
    class Player final : public Character
    {
    public:
        Player(const int8_t x, const int8_t y);

        virtual char GetSymbol() const override;
        virtual bool IsEquipmentGivable() const override;
        virtual bool IsAttackable() const override;
        virtual bool IsDamageable() const override;
        virtual void AttackTo(Character& character) override;
        virtual void OnAttack(const int16_t damage) override;

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveTo(const int8_t x, const int8_t y);
        
        int32_t GetLevel() const;
        int32_t GetMaxHp() const;
        int32_t GetBonusAttack() const;
        int32_t GetBonusDefense() const;
        int32_t GetMaxExp() const;

        void EquipArmor(Armor* armor);
        void EquipAccessory(Accessory* accessory);
        void EquipWeapon(Weapon* weapon);
        bool IsAccessoryEquippable(Accessory* accessory);
        void GainExp(const int16_t exp);

    private:
        enum
        {
            ACCESSORY_SLOT_CAPACITY = 4
        };

        int32_t mLevel;
        int32_t mMaxHp;
        Weapon* mWeapon;
        Armor* mArmor;
        std::vector<Accessory*> mAccessories;
    };
}