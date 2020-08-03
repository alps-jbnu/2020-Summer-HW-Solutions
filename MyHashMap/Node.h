#pragma once

#include <string>

template<typename T>
class Node final
{
public:
    Node(const char* const key, const T data);
    Node(const std::string& key, const T data);

    Node<T>* GetNext() const;
    void SetNext(Node<T>* const next);
    const std::string& GetKey() const;
    T GetData() const;
    void SetData(T& data);

private:
    const std::string mKey;
    T mData;
    Node<T>* mNext;
};

template<typename T>
Node<T>::Node(const char* key, const T data)
    : mNext(nullptr)
    , mKey(key)
    , mData(data)
{
}

template<typename T>
Node<T>::Node(const std::string& key, const T data)
    : Node(key.c_str(), data)
{
}

template<typename T>
Node<T>* Node<T>::GetNext() const
{
    return mNext;
}

template<typename T>
void Node<T>::SetNext(Node<T>* const next)
{
    mNext = next;
}

template<typename T>
const std::string& Node<T>::GetKey() const
{
    return mKey;
}

template<typename T>
T Node<T>::GetData() const
{
    return mData;
}

template<typename T>
void Node<T>::SetData(T& data)
{
    mData = data;
}
