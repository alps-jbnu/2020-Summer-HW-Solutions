#pragma once
#include "Map.h"

namespace rpg_extreme
{
    class GameManager final
    {
    public:
        static GameManager& GetInstance();
        void Start();
        void Exit();
        Map& GetMap() const;
        void Print() const;

    private:
        GameManager();
        ~GameManager();

        static GameManager* sInstance;
        Map* mMap;
        uint16_t mTurnCount;
        bool mbGameOver;
    };
}