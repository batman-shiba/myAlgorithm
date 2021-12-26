#include "BST.h"
#include "../seeTheTree.h"
#include <iostream>

int main() {
    vector<int> tree = {10,5,8,0,19,57};
    BST bstTree;
    bstTree.init(tree);

    vector<int> res = levelorderSeq(bstTree.getRoot());
    
    cout << endl;
    TreeNode* temp = bstTree.getRoot();
    res = levelorderSeq(temp);
    
    cout << endl;
    bstTree.insert(20);
    bstTree.insert(150);
    res = levelorderSeq(bstTree.getRoot());
    
    return 0;
}