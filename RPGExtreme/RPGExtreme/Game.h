#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>

#include "Map.h"
#include "eSymbolType.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "SpikeTrap.h"
#include "Monster.h"
#include "BossMonster.h"

namespace rpg_extreme
{
    class Game final
    {
    public:
        static Game& GetInstance();

        void Start();
        void Shutdown();
        Map& GetMap() const;
        std::string GetResultToString() const;

    private:
        Game();
        ~Game();

        void openEquipmentBox(EquipmentBox* equipmentBox);
        void battleWithBossMonster(BossMonster* bossMonster);
        void battleWithMonster(Monster* monster);
        void stepOnSpikeTrap(SpikeTrap* spikeTrap);

        static Game* sInstance;
        Map* mMap;
        uint16_t mTurnCount;
        bool mbGameClear;
        std::string mPlayerKillerName;
    };
}