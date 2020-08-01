#include <iostream>
#include <algorithm>

#include "MyHashMap.h"

bool Compare(const std::pair<std::string, bool>& p1, const std::pair<std::string, bool>& p2)
{
    return p1.first > p2.first;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    MyHashMap<bool> hashMap;

    std::cin >> N;

    for (int n = 0; n < N; ++n)
    {
        char name[6];
        char log[6];
        std::cin >> name >> log;
        hashMap.Insert(name, *log == 'e');
    }

    auto entries = hashMap.GetEntries();
    std::sort(entries.begin(), entries.end(), Compare);

    for (auto& entry : entries)
    {
        if (entry.second == true)
        {
            std::cout << entry.first << '\n';
        }
    }

    return 0;
}