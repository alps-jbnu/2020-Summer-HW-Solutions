#include "Player.h"
#include "eSymbolType.h"

namespace rpg_extreme
{
    char Player::GetSymbol() const
    {
        return eSymbolType::PLAYER;
    }
}