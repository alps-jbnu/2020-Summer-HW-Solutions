#pragma once

#include <cassert>
#include <vector>

#include "Node.h"

template<typename T, size_t CAPACITY>
class MyHashMap final
{
public:
    MyHashMap();
    ~MyHashMap();
    void Insert(const char* key, T value);
    T Get(const char* key) const;
    bool HasKey(const char* key) const;
    std::vector<std::pair<std::string, T>> GetEntries() const;

private:
    static unsigned long long sdbmHash(const char* str);
    static unsigned long long djb2Hash(const char* str);
    
    Node<T>* getNodeOrNull(const char* key) const;

    Node<T>* mContainer[CAPACITY];
};

template<typename T, size_t CAPACITY>
MyHashMap<T, CAPACITY>::MyHashMap()
{
    for (int i = 0; i < CAPACITY; ++i)
    {
        mContainer[i] = nullptr;
    }
}

template<typename T, size_t CAPACITY>
MyHashMap<T, CAPACITY>::~MyHashMap()
{
    for (int i = 0; i < CAPACITY; ++i)
    {
        Node<T>* now = mContainer[i];

        if (now == nullptr)
        {
            continue;
        }

        while (now->GetNext() != nullptr)
        {
            Node<T>* previous = now;
            now = now->GetNext();
            delete previous;
        }

        delete now;
    }
}

template<typename T, size_t CAPACITY>
void MyHashMap<T, CAPACITY>::Insert(const char* key, T value)
{
    const int index = djb2Hash(key) % CAPACITY;

    if (mContainer[index] == nullptr)
    {
        mContainer[index] = new Node<T>(key, value);

        return;
    }

    Node<T>* now = mContainer[index];
    if (now->GetKey() == key)
    {
        now->SetData(value);

        return;
    }

    while (now->GetNext() != nullptr)
    {
        if (now->GetNext()->GetKey() == key)
        {
            now->GetNext()->SetData(value);
            return;
        }

        now = now->GetNext();
    }

    now->SetNext(new Node<T>(key, value));
}

template<typename T, size_t CAPACITY>
T MyHashMap<T, CAPACITY>::Get(const char* key) const
{
    Node<T>* node = getNodeOrNull(key);
    
    assert(node != nullptr);

    return node->GetData();
}

template<typename T, size_t CAPACITY>
bool MyHashMap<T, CAPACITY>::HasKey(const char* key) const
{
    return getNodeOrNull(key) != nullptr;
}

template<typename T, size_t CAPACITY>
std::vector<std::pair<std::string, T>> MyHashMap<T, CAPACITY>::GetEntries() const
{
    std::vector<std::pair<std::string, T>> entries;
    entries.reserve(CAPACITY);

    for (Node<T>* node : mContainer)
    {
        while (node != nullptr)
        {
            entries.emplace_back(std::make_pair(node->GetKey(), node->GetData()));
            node = node->GetNext();
        }
    }

    return entries;
}

template<typename T, size_t CAPACITY>
unsigned long long MyHashMap<T, CAPACITY>::sdbmHash(const char* str)
{
    unsigned long long hash = 0;
    int c;

    while (c = *str++)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

template<typename T, size_t CAPACITY>
unsigned long long MyHashMap<T, CAPACITY>::djb2Hash(const char* str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

template<typename T, size_t CAPACITY>
Node<T>* MyHashMap<T, CAPACITY>::getNodeOrNull(const char* key) const
{
    const int index = djb2Hash(key) % CAPACITY;
    Node<T>* now = mContainer[index];

    while (now != nullptr)
    {
        if (now->GetKey() == key)
        {
            break;
        }

        now = now->GetNext();
    }

    return now;
}
