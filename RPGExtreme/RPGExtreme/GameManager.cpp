#include <iostream>
#include <string>
#include <cassert>

#include "GameManager.h"
#include "Map.h"
#include "eSymbolType.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "SpikeTrap.h"

using namespace std;

namespace rpg_extreme
{
    GameManager* GameManager::sInstance = nullptr;

    GameManager& GameManager::GetInstance()
    {
        if (sInstance == nullptr)
        {
            sInstance = new GameManager();
        }
        return *sInstance;
    }

    void GameManager::Start()
    {
        int width;
        int height;
        vector<string> mapData;

        cin >> height >> width;
        mapData.reserve(height);

        for (int i = 0; i < height; ++i)
        {
            string line;
            cin >> line;
            mapData.push_back(line);
        }

        mMap = new Map(width, height, mapData);

        string moveCommand;
        cin >> moveCommand;

        uint16_t monsterCount = mMap->GetMonsterCount();
        for (uint16_t i = 0; i < monsterCount; ++i)
        {
            int y;
            int x;
            string name;
            int attack;
            int defense;
            int maxHp;
            int exp;
            cin >> y >> x >> name >> attack >> defense >> maxHp >> exp;

            --y;
            --x;

            mMap->AddGameObject(new Monster(x, y, name, attack, defense, maxHp, exp));
        }

        uint16_t itemBoxCount = mMap->GetItemBoxCount();
        for (uint16_t i = 0; i < itemBoxCount; ++i)
        {
            int y;
            int x;
            char equipmentSymbolType;

            cin >> y >> x >> equipmentSymbolType;

            --y;
            --x;

            switch (equipmentSymbolType)
            {
            case eSymbolType::WEAPON:
                int attack;
                cin >> attack;

                mMap->AddGameObject(new EquipmentBox(x, y, new Weapon(attack)));
                break;

            case eSymbolType::ARMOR:
                int defense;
                cin >> defense;

                mMap->AddGameObject(new EquipmentBox(x, y, new Armor(defense)));
                break;

            case eSymbolType::ACCESSORY:
                char type[3];
                cin >> type;

                if (*type == 'H')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::HP_REGENERATION)));
                }
                else if (*type == 'R')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::REINCARNATION)));
                }
                else if (*type == 'C' && type[1] == 'O')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::COURAGE)));
                }
                else if (*type == 'E')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::EXPERIENCE)));
                }
                else if (*type == 'D')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::DEXTERITY)));
                }
                else if (*type == 'H')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::HUNTER)));
                }
                else if (*type == 'C' && type[1] == 'U')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryType::CURSED)));
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

        Player& player = mMap->GetPlayer();

        uint16_t moveCommandSize = moveCommand.length();
        for (mTurnCount = 0; mTurnCount < moveCommandSize && !mbGameOver; ++mTurnCount)
        {
            char d = moveCommand[mTurnCount];
            switch (d)
            {
            case 'L':
                player.MoveLeft();
                break;

            case 'R':
                player.MoveRight();
                break;

            case 'U':
                player.MoveUp();
                break;

            case 'D':
                player.MoveDown();
                break;

            default:
                assert(false);
            }

            auto& gameObjects = mMap->GetGameObjectsByXY(player.GetX(), player.GetY());
            if (gameObjects.size() > 1)
            {
                auto& gameObject = gameObjects.front();
                if (gameObject->IsAttackable())
                {
                    if (gameObject->IsDamageable())
                    {
                        Monster* monster = static_cast<Monster*>(gameObject);
                        while (true)
                        {
                            player.AttackTo(*monster);
                            if (!monster->IsAlive())
                            {
                                gameObjects.erase(gameObjects.begin());
                                player.GainExp(monster->GetExp());
                                break;
                            }

                            monster->AttackTo(player);
                            if (!player.IsAlive())
                            {
                                mbGameOver = true;
                                gameObjects.pop_back();
                                break;
                            }
                        }
                    }
                    else
                    {
                        SpikeTrap* spikeTrap = static_cast<SpikeTrap*>(gameObject);
                        player.OnAttack(5);
                    }
                }
                else if (gameObject->IsEquipmentGivable())
                {
                    EquipmentBox* equipmentBox = static_cast<EquipmentBox*>(gameObject);
                    Equipment* equipment = equipmentBox->GetEquipment();
                    if (equipment->IsAccessory())
                    {
                        Accessory* accessory = static_cast<Accessory*>(equipment);
                        if (!player.IsAccessoryEquippable(accessory))
                        {
                            continue;
                        }
                        player.EquipAccessory(accessory);
                    }
                    else if (equipment->IsArmor())
                    {
                        Armor* armor = static_cast<Armor*>(equipment);
                        player.EquipArmor(armor);
                    }
                    else if (equipment->IsWeapon())
                    {
                        Weapon* weapon = static_cast<Weapon*>(equipment);
                        player.EquipWeapon(weapon);
                    }
                    else
                    {
                        assert(false);
                    }
                    equipmentBox->Clear();
                    gameObjects.erase(gameObjects.begin());
                }
            }

            Print();
        }
    }

    void GameManager::Exit()
    {
        delete sInstance;
    }

    Map& GameManager::GetMap() const
    {
        return *mMap;
    }

    GameManager::GameManager()
        : mMap(nullptr)
        , mTurnCount(0)
        , mbGameOver(false)
    {
    }

    GameManager::~GameManager()
    {
        delete mMap;
    }

    void GameManager::Print() const
    {
        Player& player = mMap->GetPlayer();

        cout << mMap->ToString() << '\n';
        cout << "Passed Turns : " << mTurnCount << '\n';
        cout << "LV : " << player.GetLevel() << '\n';
        cout << "HP : " << player.GetHp() << '/' << player.GetMaxHp() << '\n';
        cout << "ATT : " << player.GetAttack() << '+' << player.GetBonusAttack() << '\n';
        cout << "DEF : " << player.GetDefense() << '+' << player.GetBonusDefense() << '\n';
        cout << "EXP : " << player.GetExp() << '/' << player.GetMaxExp() << '\n';
        if (mbGameOver)
        {
            if (player.IsAlive())
            {
                cout << "YOU WIN!" << '\n';
            }
            else
            {
                cout << "YOU HAVE BEEN KILLED BY " << "Boss" << ".." << '\n';
            }
        }
        else
        {
            cout << "Press any key to continue." << '\n';
        }
    }
}