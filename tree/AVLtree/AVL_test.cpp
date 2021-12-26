#include "AVL.h"
#include "../seeTheTree.h"

#include <iostream>

using namespace std; 

int main() {
    vector<int> test = {1,2,3,4,5,6,7};
    
    AVL avltree;
    avltree.init(test);

    avltree.peekTree();

    for(int i = 4; i > 0; --i) {
        avltree.erase_node(i);
    }
    avltree.peekTree();

    for(int i = 0; i < 5; ++i) {
        avltree.erase_node(i*i - 3);
    }
    avltree.peekTree();

    return 0;
}