#include <cassert>
#include <sstream>

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
        , mPlayer(nullptr)
    {
        mPassables.reserve(mHeight);
        for (int i = 0; i < mHeight; ++i)
        {
            mPassables.push_back(std::bitset<MAX_WIDTH>().set());
        }

        mGameObjects.reserve(mHeight);
        for (int y = 0; y < mHeight; ++y)
        {
            auto rowVector = std::vector<std::vector<GameObject*>>();
            rowVector.reserve(mWidth);
            
            for (int x = 0; x < mWidth; ++x)
            {
                rowVector.push_back(std::vector<GameObject*>());

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
                    rowVector[x].push_back(new SpikeTrap(x, y));
                    break;

                case eSymbolType::MONSTER:
                    ++mMonsterCount;
                    break;

                case eSymbolType::BOSS_MONSTER:
                    ++mMonsterCount;
                    break;

                case eSymbolType::PLAYER:
                    mPlayer = new Player(x, y);
                    rowVector[x].push_back(mPlayer);
                    break;
                    
                default:
                    assert(false);
                }
            }
            mGameObjects.push_back(rowVector);
        }
    }

    Map::~Map()
    {
        for (auto& rowVector : mGameObjects)
        {
            for (auto& columnVector : rowVector)
            {
                for (auto objectPtr : columnVector)
                {
                    delete objectPtr; // including mPlayer
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

    std::vector<GameObject*>& Map::GetGameObjectsByXY(const int8_t x, const int8_t y)
    {
        return mGameObjects[y][x];
    }

    void Map::AddGameObject(GameObject* gameObject)
    {
        mGameObjects[gameObject->GetY()][gameObject->GetX()].push_back(gameObject);
    }

    bool Map::IsPassable(const int8_t x, const int8_t y) const
    {
        return x >= 0 && x < mWidth && y >= 0 && y < mHeight && mPassables[y][x];
    }

    Player& Map::GetPlayer() const
    {
        return *mPlayer;
    }

    std::string Map::ToString() const
    {
        std::stringstream ss;

        for (int y = 0; y < mHeight; ++y)
        {
            for (int x = 0; x < mWidth; ++x)
            {
                auto& gameObjects = mGameObjects[y][x];
                if (gameObjects.empty())
                {
                    ss << (mPassables[y][x] ? static_cast<char>(eSymbolType::BLANK) : static_cast<char>(eSymbolType::WALL));
                }
                else
                {
                    ss << gameObjects.back()->GetSymbol();
                }
            }
            ss << '\n';
        }

        return ss.str();
    }
}
