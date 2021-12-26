#ifndef _BDNODE_
#define _BDNODE_

#include <math.h>

struct BidirectionListNode
{
    BidirectionListNode() : key(INT_MIN), val(0), prev(nullptr), next(nullptr) {}
    BidirectionListNode(int key_, int val_) : key(key_), val(val_), prev(nullptr), next(nullptr) {}

    BidirectionListNode* operator=(BidirectionListNode* other) {
        this->val = other->val;
        this->prev = other->prev;
        this->next = other->next;
        return this;
    }

    int key;
    int val;
    BidirectionListNode* prev;
    BidirectionListNode* next;    
};

#endif /* _BDNODE_ */