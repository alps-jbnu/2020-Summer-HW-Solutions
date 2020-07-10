#include <cassert>

#include "Map.h"
#include "SpikeTrap.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    Map::Map(const uint8_t width, const uint8_t height, const std::vector<std::string>& mapData)
        : mWidth(width)
        , mHeight(height)
        , mItemBoxCount(0)
        , mMonsterCount(0)
    {
        mPassables.reserve(mHeight);
        for (int i = 0; i < mHeight; ++i)
        {
            mPassables.push_back(std::bitset<MAX_WIDTH>().set());
        }

        mGameObjects.reserve(mHeight);
        for (int y = 0; y < mHeight; ++y)
        {
            auto rowVector = std::vector<std::vector<GameObject>>();
            rowVector.reserve(mWidth);
            mGameObjects.push_back(rowVector);

            for (int x = 0; x < mWidth; ++x)
            {
                rowVector.push_back(std::vector<GameObject>());

                const char symbol = mapData[y][x];

                switch (symbol)
                {
                case eSymbolType::BLANK:
                    break;

                case eSymbolType::WALL:
                    mPassables[y][x] = false;
                    break;

                case eSymbolType::ITEM_BOX:
                    ++mItemBoxCount;
                    break;

                case eSymbolType::SPIKE_TRAP:
                    //rowVector[x].push_back(SpikeTrap());
                    break;

                case eSymbolType::MONSTER:
                    ++mMonsterCount;
                    break;

                case eSymbolType::BOSS_MONSTER:
                    ++mMonsterCount;
                    break;

                case eSymbolType::PLAYER:
                    break;
                    
                default:
                    assert(false);
                }
            }
        }


    }

    uint16_t Map::GetItemBoxCount() const
    {
        return mItemBoxCount;
    }

    uint16_t Map::GetMonsterCount() const
    {
        return mMonsterCount;
    }
}
