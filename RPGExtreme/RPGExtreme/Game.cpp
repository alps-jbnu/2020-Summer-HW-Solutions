#include "Game.h"

using namespace std;

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

        // Input MoveCommand data
        string moveCommand;
        cin >> moveCommand;

        // Input monster data
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

            if (mMap->GetBossMonsterPosX() == x && mMap->GetBossMonsterPosY() == y)
            {
                mMap->AddGameObject(new BossMonster(x, y, name, attack, defense, maxHp, exp));
            }
            else
            {
                mMap->AddGameObject(new Monster(x, y, name, attack, defense, maxHp, exp));
            }
        }

        // Input Equipment data
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
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::HP_REGENERATION)));
                }
                else if (*type == 'R')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::REINCARNATION)));
                }
                else if (*type == 'C' && type[1] == 'O')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::COURAGE)));
                }
                else if (*type == 'E')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::EXPERIENCE)));
                }
                else if (*type == 'D')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::DEXTERITY)));
                }
                else if (*type == 'H')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::HUNTER)));
                }
                else if (*type == 'C' && type[1] == 'U')
                {
                    mMap->AddGameObject(new EquipmentBox(x, y, new Accessory(eAccessoryEffectType::CURSED)));
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

        uint16_t moveCommandSize = static_cast<uint16_t>(moveCommand.length());
        for (mTurnCount = 0; mTurnCount < moveCommandSize; ++mTurnCount)
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
            if (gameObjects.size() < 2)
            {
                continue;
            }

            auto& gameObject = gameObjects.front();
            if (gameObject->IsCharacter())
            {
                Monster* monster = static_cast<Monster*>(gameObject);

                if (monster->IsBoss())
                {
                    updateFightWithBossMonster(static_cast<BossMonster*>(monster));
                }
                else
                {
                    updateFightWithMonster(monster);
                }
            }
            else if (gameObject->IsEquipmentBox())
            {
                updateGainEquipmentBox(static_cast<EquipmentBox*>(gameObject));
            }
            else if (gameObject->IsSpikeTrap())
            {
                updateStepOnSpikeTrap(static_cast<SpikeTrap*>(gameObject));
            }
            else if (gameObject->IsWall())
            {

            }


            if (mbGameClear || !player.IsAlive())
            {
                break;
            }
        }

        Print();
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

    void Game::updateGainEquipmentBox(EquipmentBox* equipmentBox)
    {
        Player& player = mMap->GetPlayer();
        auto& gameObjects = mMap->GetGameObjectsByXY(player.GetX(), player.GetY());

        Equipment* equipment = equipmentBox->GetEquipment();
        if (equipment->IsAccessory())
        {
            Accessory* accessory = static_cast<Accessory*>(equipment);
            if (player.IsAccessoryEquippable(accessory))
            {
                player.EquipAccessory(accessory);
            }
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
        equipmentBox->Remove();
        gameObjects.erase(gameObjects.begin());
    }

    void Game::updateFightWithBossMonster(BossMonster* bossMonster)
    {
        Player& player = mMap->GetPlayer();
        auto& gameObjects = mMap->GetGameObjectsByXY(player.GetX(), player.GetY());

        if (player.HasAccessoryEffect(eAccessoryEffectType::HUNTER))
        {
            player.FillUpHp();
        }

        while (true)
        {
            player.AttackTo(bossMonster);
            if (!bossMonster->IsAlive())
            {
                gameObjects.erase(gameObjects.begin());
                player.AddExp(bossMonster->GetExp());

                if (player.HasAccessoryEffect(eAccessoryEffectType::HP_REGENERATION))
                {
                    //player.AddHp(3);
                }

                mbGameClear = true;

                break;
            }

            bossMonster->AttackTo(&player);
            if (!player.IsAlive())
            {
                gameObjects.pop_back();

                if (player.HasAccessoryEffect(eAccessoryEffectType::REINCARNATION))
                {
                    player.DestroyReincarnationAccessory();
                    player.MoveTo(player.GetInitX(), player.GetInitY());
                    player.FillUpHp();
                    bossMonster->FillUpHp();
                }

                break;
            }
        }
    }

    void Game::updateFightWithMonster(Monster* monster)
    {
        Player& player = mMap->GetPlayer();
        auto& gameObjects = mMap->GetGameObjectsByXY(player.GetX(), player.GetY());


        while (true)
        {
            player.AttackTo(monster);
            if (!monster->IsAlive())
            {
                gameObjects.erase(gameObjects.begin());
                player.AddExp(monster->GetExp());

                if (player.HasAccessoryEffect(eAccessoryEffectType::HP_REGENERATION))
                {
                    player.AddHp(3);
                }

                break;
            }

            monster->AttackTo(&player);
            if (!player.IsAlive())
            {
                gameObjects.pop_back();

                if (player.HasAccessoryEffect(eAccessoryEffectType::REINCARNATION))
                {
                    player.DestroyReincarnationAccessory();
                    player.MoveTo(player.GetInitX(), player.GetInitY());
                    player.FillUpHp();
                    monster->FillUpHp();
                }
                else
                {
                    mbGameClear = true;
                }


                break;
            }
        }
    }

    void Game::updateStepOnSpikeTrap(SpikeTrap* spikeTrap)
    {
        Player& player = mMap->GetPlayer();
        player.OnAttack(*spikeTrap, 5);
    }

    void Game::Print() const
    {
        Player& player = mMap->GetPlayer();

        cout << mMap->ToString() << '\n';
        cout << "Passed Turns : " << mTurnCount << '\n';
        cout << "LV : " << player.GetLevel() << '\n';
        cout << "HP : " << player.GetHp() << '/' << player.GetMaxHp() << '\n';
        cout << "ATT : " << player.GetAttack() << '+' << player.GetWeaponAttack() << '\n';
        cout << "DEF : " << player.GetDefense() << '+' << player.GetArmorDefense() << '\n';
        cout << "EXP : " << player.GetExp() << '/' << player.GetMaxExp() << '\n';

        if (mbGameClear)
        {
            cout << "YOU WIN!" << '\n';
        }
        else
        {
            if (player.IsAlive())
            {
                cout << "Press any key to continue." << '\n';
            }
            else
            {
                cout << "YOU HAVE BEEN KILLED BY " << "" << ".." << '\n';
            }
        }
    }
}