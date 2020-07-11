#include <iostream>
#include <string>
#include <cassert>

#include "GameManager.h"
#include "Map.h"
#include "eSymbolType.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"

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

                mMap->AddGameObject(new ItemBox(x, y, Weapon(attack)));
                break;

            case eSymbolType::ARMOR:
                int defense;
                cin >> defense;

                mMap->AddGameObject(new ItemBox(x, y, Armor(defense)));
                break;

            case eSymbolType::ACCESSORY:
                char type[3];
                cin >> type;

                if (*type == 'H')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::HP_REGENERATION)));
                }
                else if (*type == 'R')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::REINCARNATION)));
                }
                else if (*type == 'C' && type[1] == 'O')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::COURAGE)));
                }
                else if (*type == 'E')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::EXPERIENCE)));
                }
                else if (*type == 'D')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::DEXTERITY)));
                }
                else if (*type == 'H')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::HUNTER)));
                }
                else if (*type == 'C' && type[1] == 'U')
                {
                    mMap->AddGameObject(new ItemBox(x, y, Accessory(eAccessoryType::CURSED)));
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

        size_t moveCommandSize = moveCommand.length();
        for (size_t i = 0; i < moveCommandSize; ++i)
        {
            char d = moveCommand[i];
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
    {
    }

    GameManager::~GameManager()
    {
        delete mMap;
    }

}