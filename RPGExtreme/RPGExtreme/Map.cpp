#include "Map.h"

namespace rpg_extreme
{
    Map::Map(const uint8_t width, const uint8_t height, const std::vector<std::string>& mapData)
        : mWidth(width)
        , mHeight(height)
        , mItemBoxCount(0)
        , mMonsterCount(0)
        , mPlayer(NULL)
        , mBossMonsterPosX(0)
        , mBossMonsterPosY(0)
    {
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
                    rowVector[x].push_back(new Wall(x, y));
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
                    mBossMonsterPosX = x;
                    mBossMonsterPosY = y;
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
        Remove(mPlayer);
        delete mPlayer;

        for (auto& rowVector : mGameObjects)
        {
            for (auto& columnVector : rowVector)
            {
                for (auto objectPtr : columnVector)
                {
                    delete objectPtr;
                }
            }
        }
    }

    size_t Map::GetItemBoxCount() const
    {
        return mItemBoxCount;
    }

    size_t Map::GetMonsterCount() const
    {
        return mMonsterCount;
    }

    void Map::Spawn(GameObject* const gameObject)
    {
        mGameObjects[gameObject->GetY()][gameObject->GetX()].push_back(gameObject);
    }

    bool Map::Remove(GameObject* const gameObject)
    {
        auto& gameObjects = mGameObjects[gameObject->GetY()][gameObject->GetX()];
        auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);

        if (it == gameObjects.end())
        {
            return false;
        }

        gameObjects.erase(it);

        return true;
    }

    size_t Map::GetGameObjectCount(const int8_t x, const int8_t y) const
    {
        return mGameObjects[y][x].size();
    }

    GameObject* Map::GetGameObject(const int8_t x, const int8_t y, const uint8_t index) const
    {
        return mGameObjects[y][x][index];
    }

    bool Map::IsPassable(const int8_t x, const int8_t y) const
    {
        return x >= 0 && x < mWidth && y >= 0 && y < mHeight && (mGameObjects[y][x].empty() || !mGameObjects[y][x].front()->IsWall());
    }

    Player* Map::GetPlayer() const
    {
        return mPlayer;
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
                    ss << static_cast<char>(eSymbolType::BLANK);
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

    int8_t Map::GetBossMonsterPosX() const
    {
        return mBossMonsterPosX;
    }

    int8_t Map::GetBossMonsterPosY() const
    {
        return mBossMonsterPosY;
    }
}
