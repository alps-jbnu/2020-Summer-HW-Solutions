#include "Game.h"

namespace rpg_extreme
{
    Game* Game::sInstance = NULL;

    Game& Game::GetInstance()
    {
        if (sInstance == NULL)
        {
            sInstance = new Game();
        }
        return *sInstance;
    }

    void Game::Start()
    {
        // Input Map data
        int width;
        int height;
        std::vector<std::string> mapData;

        std::cin >> height >> width;
        mapData.reserve(height);

        for (int i = 0; i < height; ++i)
        {
            std::string line;
            std::cin >> line;
            mapData.push_back(line);
        }

        mMap = new Map(width, height, mapData);

        // Input MoveCommand data
        std::string moveCommand;
        std::cin >> moveCommand;

        // Input monster data
        size_t monsterCount = mMap->GetMonsterCount();
        for (size_t i = 0; i < monsterCount; ++i)
        {
            int y;
            int x;
            std::string name;
            int attack;
            int defense;
            int maxHp;
            int exp;

            std::cin >> y >> x >> name >> attack >> defense >> maxHp >> exp;

            --y;
            --x;

            if (mMap->GetBossMonsterPosX() == x && mMap->GetBossMonsterPosY() == y)
            {
                mMap->Spawn(new BossMonster(x, y, name, attack, defense, maxHp, exp));
            }
            else
            {
                mMap->Spawn(new Monster(x, y, name, attack, defense, maxHp, exp));
            }
        }

        // Input Equipment data
        size_t itemBoxCount = mMap->GetItemBoxCount();
        for (size_t i = 0; i < itemBoxCount; ++i)
        {
            int y;
            int x;
            char equipmentSymbolType;

            std::cin >> y >> x >> equipmentSymbolType;

            --y;
            --x;

            switch (equipmentSymbolType)
            {
            case eSymbolType::WEAPON:
                int attack;
                std::cin >> attack;
                mMap->Spawn(new EquipmentBox(x, y, new Weapon(attack)));
                break;

            case eSymbolType::ARMOR:
                int defense;
                std::cin >> defense;
                mMap->Spawn(new EquipmentBox(x, y, new Armor(defense)));
                break;

            case eSymbolType::ACCESSORY:
                char type[3];
                std::cin >> type;
                if (*type == 'H' && type[1] == 'R')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::HP_REGENERATION)));
                }
                else if (*type == 'R')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::REINCARNATION)));
                }
                else if (*type == 'C' && type[1] == 'O')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::COURAGE)));
                }
                else if (*type == 'E')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::EXPERIENCE)));
                }
                else if (*type == 'D')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::DEXTERITY)));
                }
                else if (*type == 'H' && type[1] == 'U')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::HUNTER)));
                }
                else if (*type == 'C' && type[1] == 'U')
                {
                    mMap->Spawn(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::CURSED)));
                }
                else
                {
                    assert(false);
                }
                break;

            default:
                assert(false);
            }
        }

        Player* player = mMap->GetPlayer();

        size_t moveCommandSize = moveCommand.length();
        for (mTurnCount = 0; mTurnCount < moveCommandSize; ++mTurnCount)
        {
            char d = moveCommand[mTurnCount];
            switch (d)
            {
            case 'L':
                player->MoveLeft();
                break;

            case 'R':
                player->MoveRight();
                break;

            case 'U':
                player->MoveUp();
                break;

            case 'D':
                player->MoveDown();
                break;

            default:
                assert(false);
            }

            if (mMap->GetGameObjectCount(player->GetX(), player->GetY()) < 2)
            {
                continue;
            }

            GameObject* gameObject = mMap->GetGameObject(player->GetX(), player->GetY(), 0);
            if (gameObject->IsCharacter())
            {
                Monster* monster = static_cast<Monster*>(gameObject);
                if (monster->IsBoss())
                {
                    battleWithBossMonster(static_cast<BossMonster*>(monster));
                }
                else
                {
                    battleWithMonster(monster);
                }
            }
            else if (gameObject->IsEquipmentBox())
            {
                openEquipmentBox(static_cast<EquipmentBox*>(gameObject));
            }
            else if (gameObject->IsSpikeTrap())
            {
                stepOnSpikeTrap(static_cast<SpikeTrap*>(gameObject));
            }

            if (mbGameClear || !player->IsAlive())
            {
                ++mTurnCount;
                break;
            }
        }     
    }

    void Game::Shutdown()
    {
        delete sInstance;
    }

    Map& Game::GetMap() const
    {
        return *mMap;
    }

    Game::Game()
        : mMap(NULL)
        , mTurnCount(0)
        , mbGameClear(false)
    {
    }

    Game::~Game()
    {
        delete mMap;
    }

    void Game::battleWithBossMonster(BossMonster* const bossMonster)
    {
        Player* player = mMap->GetPlayer();

        if (player->HasAccessoryEffect(eAccessoryEffectType::HUNTER))
        {
            player->SetHunterBuff();
        }

        if (player->HasAccessoryEffect(eAccessoryEffectType::COURAGE))
        {
            player->SetCourageBuff();
        }

        while (true)
        {
            player->AttackTo(bossMonster);
            if (!bossMonster->IsAlive())
            {
                player->AddExp(bossMonster->GetExp());
                if (player->HasAccessoryEffect(eAccessoryEffectType::HP_REGENERATION))
                {
                    player->AddHp(3);
                }
                mbGameClear = true;
                mMap->Remove(bossMonster);
                delete bossMonster;

                break;
            }

            bossMonster->AttackTo(player);
            if (!player->IsAlive())
            {
                if (player->HasAccessoryEffect(eAccessoryEffectType::REINCARNATION))
                {
                    player->UnequipReincarnationAccessory();
                    player->MoveTo(player->GetInitX(), player->GetInitY());
                    player->FillUpHp();
                    bossMonster->FillUpHp();
                }
                else
                {
                    mPlayerKillerName = bossMonster->GetName();
                    mMap->Remove(player);
                }

                break;
            }
        }
    }

    void Game::battleWithMonster(Monster* const monster)
    {
        Player* player = mMap->GetPlayer();

        if (player->HasAccessoryEffect(eAccessoryEffectType::COURAGE))
        {
            player->SetCourageBuff();
        }

        while (true)
        {
            player->AttackTo(monster);
            if (!monster->IsAlive())
            {
                player->AddExp(monster->GetExp());
                if (player->HasAccessoryEffect(eAccessoryEffectType::HP_REGENERATION))
                {
                    player->AddHp(3);
                }
                mMap->Remove(monster);
                delete monster;
                break;
            }

            monster->AttackTo(player);
            if (!player->IsAlive())
            {
                if (player->HasAccessoryEffect(eAccessoryEffectType::REINCARNATION))
                {
                    player->UnequipReincarnationAccessory();
                    player->MoveTo(player->GetInitX(), player->GetInitY());
                    player->FillUpHp();
                    monster->FillUpHp();
                }
                else
                {
                    mPlayerKillerName = monster->GetName();
                    mMap->Remove(player);
                }
                break;
            }
        }
    }

    void Game::openEquipmentBox(EquipmentBox* const equipmentBox)
    {
        Player* player = mMap->GetPlayer();

        Equipment* equipment = equipmentBox->GetEquipment();
        if (equipment->IsAccessory())
        {
            Accessory* accessory = static_cast<Accessory*>(equipment);
            if (player->IsAccessoryEquippable(accessory))
            {
                player->EquipAccessory(accessory);
            }
        }
        else if (equipment->IsArmor())
        {
            Armor* armor = static_cast<Armor*>(equipment);
            player->EquipArmor(armor);
        }
        else if (equipment->IsWeapon())
        {
            Weapon* weapon = static_cast<Weapon*>(equipment);
            player->EquipWeapon(weapon);
        }
        equipmentBox->Opened();
        mMap->Remove(equipmentBox);

        delete equipmentBox;
    }

    void Game::stepOnSpikeTrap(SpikeTrap* const spikeTrap)
    {
        Player* player = mMap->GetPlayer();

        spikeTrap->AttackTo(player);

        if (!player->IsAlive())
        {
            if (player->HasAccessoryEffect(eAccessoryEffectType::REINCARNATION))
            {
                player->UnequipReincarnationAccessory();
                player->MoveTo(player->GetInitX(), player->GetInitY());
                player->FillUpHp();
            }
            else
            {
                mPlayerKillerName = "SPIKE TRAP";
                mMap->Remove(player);
            }
        }
    }

    std::string Game::GetResultToString() const
    {
        std::stringstream ss;

        Player* player = mMap->GetPlayer();

        ss << mMap->ToString();
        ss << "Passed Turns : " << mTurnCount << '\n';
        ss << "LV : " << player->GetLevel() << '\n';
        ss << "HP : " << player->GetHp() << '/' << player->GetMaxHp() << '\n';
        ss << "ATT : " << player->GetAttack() << '+' << player->GetWeaponAttack() << '\n';
        ss << "DEF : " << player->GetDefense() << '+' << player->GetArmorDefense() << '\n';
        ss << "EXP : " << player->GetExp() << '/' << player->GetMaxExp() << '\n';

        if (mbGameClear)
        {
            ss << "YOU WIN!" << '\n';
        }
        else
        {
            if (player->IsAlive())
            {
                ss << "Press any key to continue." << '\n';
            }
            else
            {
                ss << "YOU HAVE BEEN KILLED BY " << mPlayerKillerName << ".." << '\n';
            }
        }

        ss << '\n';

        return ss.str();
    }
}