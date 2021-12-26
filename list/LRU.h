/*
LRU是一种内存置换算法，用于发生缺页中断而物理内存又已经满了的情况，
这是需要选择一些页面与目标页面交换。
LRU的实现应当维护一个页面链表，头部是最近使用过的页面，尾部是最近都未使用的页面，
当超过容量时把尾部页面换出即可。

实际上这种做法非常耗费资源，链表太长的时候耗费的时间很多，我们可以用哈希表来节约时间。
*/

#include "BidirectionNode.h"

#include <unordered_map>

class LRUCache {
    public:
        LRUCache(int maxSize) : capacity(maxSize), 
                                head(new BidirectionListNode()), 
                                tail(new BidirectionListNode())
        {
            head->next = tail;
            tail->prev = head;
        }

        int get(int key) {
            if(mp.find(key) == mp.end()) {
                return -1;
            }

            int res = mp[key]->val;
            moveToHead(mp[key]);
            return res;
        }

        void put(int key, int value) {
            if(mp.find(key) != mp.end()) {
                mp[key]->val = value;
                moveToHead(mp[key]);
            }
            else {
                BidirectionListNode* newNode = new BidirectionListNode(key, value);
                insertToHead(newNode);
                mp[key] = newNode;

                if(mp.size() > capacity) {
                    int theKey = removeTail();
                    mp.erase(theKey);
                }
            }

        }
    
    private:
        int capacity;
        BidirectionListNode* head;
        BidirectionListNode* tail;
        std::unordered_map<int, BidirectionListNode*> mp;

        void insertToHead(BidirectionListNode* node);
        void moveToHead(BidirectionListNode* node);
        int removeTail();
};

void LRUCache::insertToHead(BidirectionListNode* node) {
    BidirectionListNode* next = head->next;

    head->next = node;
    node->next = next;
    node->prev = head;
    next->prev = node;
}

void LRUCache::moveToHead(BidirectionListNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    insertToHead(node);
}

int LRUCache::removeTail() {
    BidirectionListNode* lastNode = tail->prev;
    int key = lastNode->key;

    tail->prev = lastNode->prev;
    lastNode->prev = tail;

    //delete lastNode;

    return key;
}
