#ifndef _LISTNODE_
#define _LISTNODE_

struct ListNode
{
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val_) : val(val_), next(nullptr) {}

    ListNode* operator=(ListNode* other) {
        this->val = other->val;
        this->next = other->next;
        return this;
    }

    int val;
    ListNode* next;    
};

#endif /*_LISTNODE_*/