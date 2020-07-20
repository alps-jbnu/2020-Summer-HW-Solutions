#include <cassert>

#include "Player.h"
#include "eSymbolType.h"
#include "Game.h"

namespace rpg_extreme
{
    Player::Player(const int8_t x, const int8_t y)
        : Character(x, y, 2, 2, 20, 0)
        , mLevel(1)
        , mWeapon(NULL)
        , mArmor(NULL)
        , mInitX(x)
        , mInitY(y)
        , mbCourageBuff(false)
        , mbHunterBuff(false)
    {
        mAccessories.reserve(ACCESSORY_SLOT_CAPACITY);
    }

    char Player::GetSymbol() const
    {
        return eSymbolType::PLAYER;
    }

    bool Player::IsPlayer() const
    {
        return true;
    }

    bool Player::IsMonster() const
    {
        return false;
    }

    bool Player::IsAttackable() const
    {
        return true;
    }

    bool Player::IsAttackedable() const
    {
        return true;
    }

    void Player::AttackTo(Character* character)
    {
        assert(this != character);

        Monster* monster = static_cast<Monster*>(character);

        int16_t damage = mAttack + GetWeaponAttack();

        if (mbCourageBuff)
        {
            if (HasAccessoryEffect(eAccessoryEffectType::DEXTERITY))
            {
                damage *= 3;
            }
            else
            {
                damage <<= 1;
            }
            mbCourageBuff = false;
        }

        damage -= monster->GetDefense();
        
        if (damage <= 0)
        {
            damage = 1;
        }

        monster->OnAttack(this, damage);
    }

    void Player::OnAttack(GameObject* gameObject, const int16_t damage)
    {
        if (gameObject->IsCharacter())
        {
            Monster* monster = static_cast<Monster*>(gameObject);

            if (monster->IsBoss())
            {
                if (mbHunterBuff)
                {
                    mbHunterBuff = false;
                    return;
                }
            }

            mHp -= damage;
        }
        else if (gameObject->IsSpikeTrap())
        {
            if (HasAccessoryEffect(eAccessoryEffectType::DEXTERITY))
            {
                --mHp;
            }
            else
            {
                mHp -= damage;
            }
        }

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
        Map& map = Game::GetInstance().GetMap();
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

    int16_t Player::GetLevel() const
    {
        return mLevel;
    }

    int16_t Player::GetWeaponAttack() const
    {
        if (mWeapon == NULL)
        {
            return 0;
        }
        return mWeapon->GetAttack();
    }

    int16_t Player::GetArmorDefense() const
    {
        if (mArmor == NULL)
        {
            return 0;
        }
        return mArmor->GetDefense();
    }

    int16_t Player::GetMaxExp() const
    {
        return 5 * mLevel;
    }

    int8_t Player::GetInitX() const
    {
        return mInitX;
    }

    int8_t Player::GetInitY() const
    {
        return mInitY;
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

    bool Player::IsAccessoryEquippable(const Accessory* accessory) const
    {
        if (mAccessories.size() >= ACCESSORY_SLOT_CAPACITY)
        {
            return false;
        }

        auto type = accessory->GetType();
        for (const auto& equippedAccessory : mAccessories)
        {
            if (equippedAccessory->GetType() == type)
            {
                return false;
            }
        }

        return true;
    }

    bool Player::HasAccessoryEffect(const eAccessoryEffectType accesoryEffectType) const
    {
        for (const auto& equippedAccessory : mAccessories)
        {
            if (equippedAccessory->GetType() == accesoryEffectType)
            {
                return true;
            }
        }

        return false;
    }

    void Player::AddExp(int16_t exp)
    {
        if (HasAccessoryEffect(eAccessoryEffectType::EXPERIENCE))
        {
            exp = static_cast<uint16_t>(exp * 1.2);
        }

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

    void Player::AddHp(const int16_t hp)
    {
        mHp += hp;
        if (mHp > mMaxHp)
        {
            mHp = mMaxHp;
        }
    }

    void Player::DestroyReincarnationAccessory()
    {
        for (std::vector<Accessory*>::iterator it = mAccessories.begin(); it != mAccessories.end();)
        {
            if ((*it)->GetType() == eAccessoryEffectType::REINCARNATION)
            {
                mAccessories.erase(it);
                return;
            }
        }
    }

    void Player::SetCourageBuff()
    {
        mbCourageBuff = true;
    }

    void Player::SetHunterBuff()
    {
        mbHunterBuff = true;
        FillUpHp();
    }
}