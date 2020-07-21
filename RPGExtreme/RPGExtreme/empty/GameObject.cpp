#include "GameObject.h"

namespace rpg_extreme
{
    GameObject::GameObject(const int8_t x, const int8_t y)
        : mX(0)
        , mY(0)
    {
    }

    GameObject::~GameObject()
    {
    }

    int8_t GameObject::GetX() const
    {
        return 0;
    }

    int8_t GameObject::GetY() const
    {
        return 0;
    }
}