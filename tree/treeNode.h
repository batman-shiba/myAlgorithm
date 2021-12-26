#ifndef _TREENODE_
#define _TREENODE_

#include <limits.h>

struct TreeNode
{
    TreeNode(int num) : left(nullptr), right(nullptr), val(num) {}
    TreeNode() : left(nullptr), right(nullptr), val(INT_MIN) {}
    
    TreeNode* operator= (TreeNode* other) {
        this->left = other->left;
        this->right = other->right;
        this->val = other->val;
        return this;
    }

    TreeNode* left;
    TreeNode* right;
    int val;
};

#endif /* _TREENODE_ */