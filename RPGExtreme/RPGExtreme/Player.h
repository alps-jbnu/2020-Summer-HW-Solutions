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
        virtual void AttackTo(Character* const character);
        virtual void OnAttack(GameObject* const gameObject, const int16_t damage);

        void MoveTo(const int8_t x, const int8_t y);
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        
        void AddHp(const int16_t hp);
        void AddExp(uint16_t exp);

        void EquipArmor(Armor* const armor);
        void EquipAccessory(Accessory* const accessory);
        void UnequipReincarnationAccessory();
        void EquipWeapon(Weapon* const weapon);
        
        bool IsAccessoryEquippable(const Accessory* const accessory) const;
        bool HasAccessoryEffect(const eAccessoryEffectType accesoryEffectType) const;

        void SetCourageBuff();
        void SetHunterBuff();

        uint16_t GetLevel() const;
        uint16_t GetMaxExp() const;
        int16_t GetWeaponAttack() const;
        int16_t GetArmorDefense() const;
        int8_t GetInitX() const;
        int8_t GetInitY() const;

    private:
        enum
        {
            ACCESSORY_SLOT_CAPACITY = 4
        };

        uint16_t mLevel;
        Weapon* mWeapon;
        Armor* mArmor;
        std::vector<Accessory*> mAccessories;

        bool mbCourageBuff;
        bool mbHunterBuff;

        const int8_t mInitX;
        const int8_t mInitY;
    };
}
