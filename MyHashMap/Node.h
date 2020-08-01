#pragma once

#include <string>

class Node final
{
public:
    Node(const char* const key, const int data);

    Node* GetNext() const;
    void SetNext(Node* const next);
    const std::string& GetKey() const;
    int GetData() const;

private:
    std::string mKey;
    int mData;
    Node* mNext;
};