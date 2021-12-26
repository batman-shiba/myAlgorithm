/*
遍历一颗二叉树有以下几种方法：
层序遍历、先序遍历、中序遍历、后序遍历，
层序遍历按层输出，最为清晰地看出一棵树的层级结构
（反正先序、中序、后序的输出我是看不懂）
先序遍历顺序为中左右
中序遍历顺序为左中右
后序遍历顺序为左右中
*/
#pragma once
#include "treeNode.h"
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <string>
using namespace std;

// 层序遍历
vector<int> levelorderSeq(TreeNode* root) {
    TreeNode* node = root;
    vector<int> res;
    if(root == nullptr) {
        return res;
    }

    queue<TreeNode*> que;
    que.push(node);

    while(!que.empty()) {
        node = que.front();
        que.pop();
        res.push_back(node->val);

        if(node->left != nullptr)
            que.push(node->left);
        if(node->right != nullptr)
            que.push(node->right);
    }

    return res;
}

// 先序遍历，遍历节点顺序为中左右
vector<int> preorderSeq(TreeNode* root) {
    vector<int> res;
    if(nullptr == root) {
        return res;
    }
    TreeNode* node = root;
    stack<TreeNode*> stk;

    while(!stk.empty() || node != nullptr) {
        // 先遍历中间节点
        while(node != nullptr) {
            stk.push(node);
            res.push_back(node->val);
            node = node->left;
        }
        
        node = stk.top();
        stk.pop();
        node = node->right;
    }
    return res;
}

// 中序遍历，遍历节点顺序为左中右
vector<int> inorderSeq(TreeNode* root) {
    vector<int> res;
    if(nullptr == root) {
        return res;
    }
    TreeNode* node = root;
    stack<TreeNode*> stk;

    while(!stk.empty() || node != nullptr) {
        while(node != nullptr) {
            stk.push(node);
            node = node->left;
        }
        
        node = stk.top();
        stk.pop();
        // 先遍历左节点
        res.push_back(node->val);
        node = node->right;
    }
    return res;
}

// 后序遍历，遍历节点顺序为左右中
// 一种优雅的做法是倒转前序遍历对于子节点的遍历过程，即中右左，再将结果整个reverse
vector<int> postorderSeq(TreeNode* root) {
    vector<int> res;
    if(nullptr == root) {
        return res;
    }
    TreeNode* node = root;
    stack<TreeNode*> stk;

    while(!stk.empty() || node != nullptr) {
        // 先遍历中间节点
        while(node != nullptr) {
            stk.push(node);
            res.push_back(node->val);
            node = node->right;
        }
        
        node = stk.top();
        stk.pop();
        node = node->left;
    }
    reverse(res.begin(), res.end());
    return res;
}
