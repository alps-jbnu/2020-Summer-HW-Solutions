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
    
    void Insert(const char* const key, T value);
    void Insert(const std::string& key, T value);
    bool Delete(const char* const key);
    bool Delete(const std::string& key);
    T Get(const char* const key) const;
    T Get(const std::string& key) const;
    bool HasKey(const char* const key) const;
    bool HasKey(const std::string& key) const;
    std::vector<std::pair<std::string, T>> GetEntries() const;

private:
    static unsigned long long sdbmHash(const char* str);
    static unsigned long long djb2Hash(const char* str);
    
    Node<T>* getNodeOrNull(const char* key) const;

    Node<T>* mNodes[CAPACITY];
};

template<typename T, size_t CAPACITY>
MyHashMap<T, CAPACITY>::MyHashMap()
    : mNodes()
{
    for (size_t i = 0; i < CAPACITY; ++i)
    {
        mNodes[i] = nullptr;
    }
}

template<typename T, size_t CAPACITY>
MyHashMap<T, CAPACITY>::~MyHashMap()
{
    for (size_t i = 0; i < CAPACITY; ++i)
    {
        Node<T>* currentNode = mNodes[i];

        if (currentNode == nullptr)
        {
            continue;
        }

        while (currentNode->GetNext() != nullptr)
        {
            Node<T>* previous = currentNode;
            currentNode = currentNode->GetNext();
            delete previous;
        }

        delete currentNode;
    }
}

template<typename T, size_t CAPACITY>
void MyHashMap<T, CAPACITY>::Insert(const char* const key, T value)
{
    const size_t index = djb2Hash(key) % CAPACITY;

    if (mNodes[index] == nullptr)
    {
        mNodes[index] = new Node<T>(key, value);

        return;
    }

    Node<T>* currentNode = mNodes[index];
    if (currentNode->GetKey() == key)
    {
        currentNode->SetData(value);

        return;
    }

    while (currentNode->GetNext() != nullptr)
    {
        if (currentNode->GetNext()->GetKey() == key)
        {
            currentNode->GetNext()->SetData(value);
            return;
        }

        currentNode = currentNode->GetNext();
    }

    currentNode->SetNext(new Node<T>(key, value));
}

template<typename T, size_t CAPACITY>
void MyHashMap<T, CAPACITY>::Insert(const std::string& key, T value)
{
    return Insert(key.c_str(), value);
}

template<typename T, size_t CAPACITY>
bool MyHashMap<T, CAPACITY>::Delete(const char* const key)
{
    const size_t index = djb2Hash(key) % CAPACITY;
    Node<T>* currentNode = mNodes[index];

    if (currentNode == nullptr)
    {
        return false;
    }

    if (currentNode->GetKey() == key)
    {
        Node<T>* temp = currentNode;
        mNodes[index] = currentNode->GetNext();
        delete temp;

        return true;
    }

    while (currentNode->GetNext() != nullptr)
    {
        if (currentNode->GetNext()->GetKey() == key)
        {
            Node<T>* temp = currentNode->GetNext();
            currentNode->SetNext(currentNode->GetNext()->GetNext());
            delete temp;

            return true;
        }

        currentNode = currentNode->GetNext();
    }

    return false;
}

template<typename T, size_t CAPACITY>
bool MyHashMap<T, CAPACITY>::Delete(const std::string& key)
{
    return Delete(key.c_str());
}

template<typename T, size_t CAPACITY>
T MyHashMap<T, CAPACITY>::Get(const char* const key) const
{
    Node<T>* node = getNodeOrNull(key);
    
    assert(node != nullptr);

    return node->GetData();
}

template<typename T, size_t CAPACITY>
T MyHashMap<T, CAPACITY>::Get(const std::string& key) const
{
    Node<T>* node = getNodeOrNull(key.c_str());

    assert(node != nullptr);

    return node->GetData();
}

template<typename T, size_t CAPACITY>
bool MyHashMap<T, CAPACITY>::HasKey(const char* const key) const
{
    return getNodeOrNull(key) != nullptr;
}

template<typename T, size_t CAPACITY>
inline bool MyHashMap<T, CAPACITY>::HasKey(const std::string& key) const
{
    return getNodeOrNull(key.c_str()) != nullptr;
}

template<typename T, size_t CAPACITY>
std::vector<std::pair<std::string, T>> MyHashMap<T, CAPACITY>::GetEntries() const
{
    std::vector<std::pair<std::string, T>> entries;
    entries.reserve(CAPACITY);

    for (Node<T>* node : mNodes)
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
    const size_t index = djb2Hash(key) % CAPACITY;
    Node<T>* currentNode = mNodes[index];

    while (currentNode != nullptr)
    {
        if (currentNode->GetKey() == key)
        {
            break;
        }

        currentNode = currentNode->GetNext();
    }

    return currentNode;
}
