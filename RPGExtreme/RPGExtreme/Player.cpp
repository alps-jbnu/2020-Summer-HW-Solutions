#include "Game.h"
#include "Player.h"

namespace rpg_extreme
{
    Player::Player(const int8_t x, const int8_t y)
        : Character(x, y, 2, 2, 20, 0)
        , mLevel(1)
        , mWeapon(nullptr)
        , mArmor(nullptr)
        , mInitX(x)
        , mInitY(y)
        , mbCourageBuff(false)
        , mbHunterBuff(false)
    {
        mAccessories.reserve(ACCESSORY_SLOT_CAPACITY);
    }

    Player::~Player()
    {
        delete mWeapon;
        delete mArmor;
        for (Accessory* accessory : mAccessories)
        {
            delete accessory;
        }
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

    void Player::AttackTo(Character* const character)
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

        monster->OnAttacked(this, damage);
    }

    void Player::OnAttacked(GameObject* const gameObject, const int16_t damage)
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

        if (mHp < 0)
        {
            mHp = 0;
        }
    }

    void Player::MoveTo(const int8_t x, const int8_t y)
    {
        Map& map = Game::GetInstance().GetMap();
        if (map.IsPassable(x, y))
        {
            map.Remove(this);
            mX = x;
            mY = y;
            map.Spawn(this);
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

    void Player::AddHp(const int16_t hp)
    {
        mHp += hp;
        if (mHp > mMaxHp)
        {
            mHp = mMaxHp;
        }
    }

    void Player::AddExp(uint16_t exp)
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

    void Player::EquipArmor(Armor* const armor)
    {
        delete mArmor;
        mArmor = armor;
    }

    void Player::EquipAccessory(Accessory* const accessory)
    {
        mAccessories.push_back(accessory);
    }

    void Player::UnequipReincarnationAccessory()
    {
        for (std::vector<Accessory*>::iterator it = mAccessories.begin(); it != mAccessories.end();)
        {
            if ((*it)->GetType() == eAccessoryEffectType::REINCARNATION)
            {
                delete *it;
                it = mAccessories.erase(it);
                return;
            }
            ++it;
        }
    }

    void Player::EquipWeapon(Weapon* const weapon)
    {
        delete mWeapon;
        mWeapon = weapon;
    }

    bool Player::IsAccessoryEquippable(const Accessory* const accessory) const
    {
        if (mAccessories.size() >= ACCESSORY_SLOT_CAPACITY)
        {
            return false;
        }

        const eAccessoryEffectType type = accessory->GetType();
        for (const Accessory* equippedAccessory : mAccessories)
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

    void Player::SetCourageBuff()
    {
        mbCourageBuff = true;
    }

    void Player::SetHunterBuff()
    {
        mbHunterBuff = true;
        FillUpHp();
    }

    uint16_t Player::GetLevel() const
    {
        return mLevel;
    }

    uint16_t Player::GetMaxExp() const
    {
        return 5 * mLevel;
    }

    int16_t Player::GetWeaponAttack() const
    {
        if (mWeapon == nullptr)
        {
            return 0;
        }
        return mWeapon->GetAttack();
    }

    int16_t Player::GetArmorDefense() const
    {
        if (mArmor == nullptr)
        {
            return 0;
        }
        return mArmor->GetDefense();
    }

    int8_t Player::GetInitX() const
    {
        return mInitX;
    }

    int8_t Player::GetInitY() const
    {
        return mInitY;
    }
}