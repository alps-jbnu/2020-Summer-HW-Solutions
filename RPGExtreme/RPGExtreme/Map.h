#pragma once

#include <cstdint>
#include <vector>
#include <bitset>

#include "GameObject.h"

namespace rpg_extreme
{
    class Map final
    {
    public:
        Map(const uint8_t width, const uint8_t height, const std::vector<std::string>& mapData);
        uint16_t GetItemBoxCount() const;
        uint16_t GetMonsterCount() const;

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

        std::vector<std::bitset<MAX_WIDTH>> mPassables;
        std::vector<std::vector<std::vector<GameObject>>> mGameObjects;

    };
}