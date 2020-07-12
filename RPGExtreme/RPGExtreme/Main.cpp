#include <iostream>

#include "GameManager.h"

using namespace rpg_extreme;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    GameManager& gameManager = GameManager::GetInstance();
    gameManager.Start();
    gameManager.Exit();

    return 0;
}