#include "Player.h"
#include "eSymbolType.h"
#include "GameManager.h"

namespace rpg_extreme
{
    Player::Player(const int8_t x, const int8_t y)
        : Character(x, y, 2, 2, 20, 0)
        , mLevel(1)
        , mMaxHp(mHp)
    {
    }

    char Player::GetSymbol() const
    {
        return eSymbolType::PLAYER;
    }

    void Player::MoveLeft()
    {
        MoveTo(mX - 1, mY);
    }

    void Player::MoveRight()
    {
        MoveTo(mX + 1, mY);
    }

    void Player::MoveUp()
    {
        MoveTo(mX, mY - 1);
    }

    void Player::MoveDown()
    {
        MoveTo(mX, mY + 1);
    }

    void Player::MoveTo(const int8_t x, const int8_t y)
    {
        Map& map = GameManager::GetInstance().GetMap();
        if (map.IsPassable(x, y))
        {
            auto& gameObjects = map.GetGameObjectsByXY(mX, mY);
            auto player = gameObjects.back();
            gameObjects.pop_back();
            map.GetGameObjectsByXY(x, y).push_back(player);
            mX = x;
            mY = y;
        }
    }
}