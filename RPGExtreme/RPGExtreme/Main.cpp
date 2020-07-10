#include <iostream>
#include <string>

#include "Map.h"

using namespace std;
using namespace rpg_extreme;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int width;
    int height;
    vector<string> mapData;

    cin >> height >> width;
    mapData.reserve(height);

    for (int i = 0; i < height; ++i)
    {
        string line;
        cin >> line;
        mapData.push_back(line);
    }

    Map map(width, height, mapData);



    return 0;
}