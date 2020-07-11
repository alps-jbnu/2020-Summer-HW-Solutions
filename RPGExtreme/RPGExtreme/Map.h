#pragma once

#include <cstdint>
#include <vector>
#include <bitset>

#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "ItemBox.h"

namespace rpg_extreme
{
    class Map final
    {
    public:
        Map(const uint8_t width, const uint8_t height, const std::vector<std::string>& mapData);
        ~Map();

        uint16_t GetItemBoxCount() const;
        uint16_t GetMonsterCount() const;
        void AddGameObject(GameObject* gameObject);
        std::vector<GameObject*>& GetGameObjectsByXY(const int8_t x, const int8_t y);
        bool IsPassable(const int8_t x, const int8_t y) const;
        Player& GetPlayer() const;

    private:
        enum
        {
            MAX_WIDTH = 100,
            MAX_HEIGHT = 100
        };

        const uint8_t mWidth;
        const uint8_t mHeight;
        uint16_t mItemBoxCount;
        uint16_t mMonsterCount;
        Player* mPlayer;

        std::vector<std::bitset<MAX_WIDTH>> mPassables;
        std::vector<std::vector<std::vector<GameObject*>>> mGameObjects;
    };
}