#include <cassert>

#include "Player.h"
#include "eSymbolType.h"
#include "GameManager.h"

namespace rpg_extreme
{
    Player::Player(const int8_t x, const int8_t y)
        : Character(x, y, 2, 2, 20, 0)
        , mLevel(1)
        , mMaxHp(mHp)
        , mWeapon(nullptr)
        , mArmor(nullptr)
    {
        mAccessories.reserve(ACCESSORY_SLOT_CAPACITY);
    }

    char Player::GetSymbol() const
    {
        return eSymbolType::PLAYER;
    }

    bool Player::IsEquipmentGivable() const
    {
        return false;
    }

    bool Player::IsAttackable() const
    {
        return false;
    }

    bool Player::IsDamageable() const
    {
        return false;
    }

    void Player::AttackTo(Character& character)
    {
        assert(this != &character);
        int16_t damage = mAttack + GetBonusAttack() - character.GetDefense();
        if (damage <= 0)
        {
            damage = 1;
        }
        character.OnAttack(damage);
    }

    void Player::OnAttack(const int16_t damage)
    {
        mHp -= damage;
        if (mHp <= 0)
        {
            mHp = 0;
        }
    }

    void Player::MoveLeft()
    {
        MoveTo(mX - 1, mY);
    }

    void Player::MoveRight()
    {
        MoveTo(mX + 1, mY);
    }

    void Player::MoveUp()
    {
        MoveTo(mX, mY - 1);
    }

    void Player::MoveDown()
    {
        MoveTo(mX, mY + 1);
    }

    void Player::MoveTo(const int8_t x, const int8_t y)
    {
        Map& map = GameManager::GetInstance().GetMap();
        if (map.IsPassable(x, y))
        {
            auto& gameObjects = map.GetGameObjectsByXY(mX, mY);
            auto& player = gameObjects.back();
            gameObjects.pop_back();
            map.GetGameObjectsByXY(x, y).push_back(player);
            mX = x;
            mY = y;
        }
    }

    int32_t Player::GetLevel() const
    {
        return mLevel;
    }

    int32_t Player::GetMaxHp() const
    {
        return mMaxHp;
    }

    int32_t Player::GetBonusAttack() const
    {
        if (mWeapon == nullptr)
        {
            return 0;
        }
        return mWeapon->GetAttack();
    }

    int32_t Player::GetBonusDefense() const
    {
        if (mArmor == nullptr)
        {
            return 0;
        }
        return mArmor->GetDefense();
    }

    int32_t Player::GetMaxExp() const
    {
        return 5 * mLevel;
    }

    void Player::EquipArmor(Armor* armor)
    {
        mArmor = armor;
    }

    void Player::EquipAccessory(Accessory* accessory)
    {
        mAccessories.push_back(accessory);
    }

    void Player::EquipWeapon(Weapon* weapon)
    {
        mWeapon = weapon;
    }

    bool Player::IsAccessoryEquippable(Accessory* accessory)
    {
        if (mAccessories.size() >= ACCESSORY_SLOT_CAPACITY)
        {
            return false;
        }

        auto type = accessory->GetType();
        for (auto& equippedAccessory : mAccessories)
        {
            if (equippedAccessory->GetType() == type)
            {
                return false;
            }
        }

        return true;
    }

    void Player::GainExp(const int16_t exp)
    {
        mExp += exp;
        if (mExp >= GetMaxExp())
        {
            ++mLevel;
            mMaxHp += 5;
            mAttack += 2;
            mDefense += 2;
            mHp = mMaxHp;
            mExp = 0;
        }
    }
}