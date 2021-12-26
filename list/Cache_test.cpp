#include "BidirectionNode.h"
#include "LRU.h"
#include "LFU.h"

#include <vector>
#include <iostream>
using namespace std;

int main() {
    LRUCache* lruCache = new LRUCache(3);
    cout << "LRUcache Test" << endl;

    for(int i = 0; i < 5; ++i) {
        lruCache->put(i, i+2);
        cout << lruCache->get(i-1) << endl;
    }

    cout << lruCache->get(3) << endl;
    cout << "LFUcache Test" << endl;

    LFUCache* lfuCache = new LFUCache(3);

    for(int i = 0; i < 5; ++i) {
        lfuCache->put(i, i + 3);
        cout << lfuCache->get(2) << endl;
    }

    return 0;
}