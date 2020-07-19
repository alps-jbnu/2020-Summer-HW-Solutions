#pragma once

#include "GameObject.h"

namespace rpg_extreme
{
    class Character : public GameObject
    {
    public:
        virtual bool IsCharacter() const override;
        virtual bool IsEquipmentBox() const override;
        virtual bool IsWall() const override;
        virtual bool IsSpikeTrap() const override;

        virtual bool IsPlayer() const;
        virtual bool IsMonster() const;

        int16_t GetHp() const;
        int16_t GetMaxHp() const;
        int16_t GetAttack() const;
        int16_t GetDefense() const;
        int16_t GetExp() const;

        bool IsAlive() const;
        void FillUpHp();

    protected:
        Character(const int8_t x, const int8_t y, const int16_t attack, const int16_t defense, const int16_t hp, const int16_t exp);

        int16_t mHp;
        int16_t mMaxHp;
        int16_t mAttack;
        int16_t mDefense;
        int16_t mExp;
    };
}