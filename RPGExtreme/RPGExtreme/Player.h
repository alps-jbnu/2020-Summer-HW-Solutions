#pragma once

#include <cstdint>
#include <vector>

#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "IAttackable.h"
#include "IAttackedable.h"

namespace rpg_extreme
{
    class Player final : public Character, public IAttackable, public IAttackedable
    {
    public:
        Player(const int8_t x, const int8_t y);

        virtual char GetSymbol() const;
        virtual bool IsPlayer() const;
        virtual bool IsMonster() const;

        virtual bool IsAttackable() const;
        virtual bool IsAttackedable() const;
        virtual void AttackTo(Character* character);
        virtual void OnAttack(GameObject* gameObject, const int16_t damage);

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveTo(const int8_t x, const int8_t y);
        
        int16_t GetLevel() const;
        int16_t GetWeaponAttack() const;
        int16_t GetArmorDefense() const;
        int16_t GetMaxExp() const;
        int8_t GetInitX() const;
        int8_t GetInitY() const;

        void EquipArmor(Armor* armor);
        void EquipAccessory(Accessory* accessory);
        void EquipWeapon(Weapon* weapon);
        bool IsAccessoryEquippable(const Accessory* accessory) const;
        bool HasAccessoryEffect(const eAccessoryEffectType accesoryEffectType) const;
        void AddExp(int16_t exp);
        void AddHp(const int16_t hp);
        void DestroyReincarnationAccessory();
        void SetCourageBuff();
        void SetHunterBuff();

    private:
        enum
        {
            ACCESSORY_SLOT_CAPACITY = 4
        };

        const int8_t mInitX;
        const int8_t mInitY;

        int16_t mLevel;
        Weapon* mWeapon;
        Armor* mArmor;
        std::vector<Accessory*> mAccessories;

        bool mbCourageBuff;
        bool mbHunterBuff;
    };
}
