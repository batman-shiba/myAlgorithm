#include "./BSTtree/BST.h"
#include "seeTheTree.h"
#include "otherCommonAlgorithm.h"
#include <iostream>

void printfVec(vector<int>& arr) {
    for(int& num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // bst
    vector<int> build = {7,1,10,3,4,7,9,45};

    BST bst_tree;
    bst_tree.init(build);

    // 先序
    vector<int> vec;
    cout << "preorder" << endl;
    vec = preorderSeq(bst_tree.getRoot());
    printfVec(vec);
    
    // 中序
    cout << "inorder" << endl;
    vec = inorderSeq(bst_tree.getRoot());
    printfVec(vec);

    // 后序
    cout << "postorder" << endl;
    vec = postorderSeq(bst_tree.getRoot());
    printfVec(vec);

    // 层序
    cout << "floorseq" << endl;
    vec = levelorderSeq(bst_tree.getRoot());
    printfVec(vec);

    // 序列化
    cout << "serialize" << endl;
    string s = "";
    serialize(bst_tree.getRoot(), s);
    cout << s << endl;

    // 反序列化
    cout << "reserialize" << endl;
    TreeNode* root = reserialize(s);
    vec = levelorderSeq(root);
    printfVec(vec);

    return 0;
}