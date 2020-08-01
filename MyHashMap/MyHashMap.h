#pragma once
#include "Node.h"

class MyHashMap
{
public:
    void Insert(const char* key, const int value);
    int Get(const char* key) const;

private:
    enum
    {
        CAPACITY = 59
    };

    Node* mContainer[CAPACITY];
};