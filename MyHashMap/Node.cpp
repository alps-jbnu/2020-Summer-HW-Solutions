#include "Node.h"

Node::Node(const char* key, const int data)
    : mNext(nullptr)
    , mKey(key)
    , mData(data)
{
}

Node* Node::GetNext() const
{
    return mNext;
}

void Node::SetNext(Node* const next)
{
    mNext = next;
}

const std::string& Node::GetKey() const
{
    return mKey;
}

int Node::GetData() const
{
    return mData;
}