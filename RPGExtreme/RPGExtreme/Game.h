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
        void Print() const;

    private:
        Game();
        ~Game();

        void updateGainEquipmentBox(EquipmentBox* equipmentBox);
        void updateFightWithBossMonster(BossMonster* bossMonster);
        void updateFightWithMonster(Monster* monster);
        void updateStepOnSpikeTrap(SpikeTrap* spikeTrap);

        static Game* sInstance;
        Map* mMap;
        uint16_t mTurnCount;
        bool mbGameClear;
    };
}