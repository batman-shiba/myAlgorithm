#include "treeNode.h"
#include <queue>
#include <string>
#include <algorithm>

using std::queue;
using std::string;

// 仅用于二叉搜索树
int maxNodeVal(TreeNode* root) {
    while(root->right != nullptr) {
        root = root->right;
    }
    return root->val;
}
// 仅用于二叉搜索树
int minNodeVal(TreeNode* root) {
    while(root->left != nullptr) {
        root = root->left;
    }
    return root->val;
}
// 以先序遍历序列化
void serialize(TreeNode* node, string& str) {
    if(node == nullptr) {
        str += "nullptr,";
    }
    else {
        str += std::to_string(node->val) + ',';
        serialize(node->left, str);
        serialize(node->right, str);
    }
}
// 以先序遍历反序列化
TreeNode* reserialize_aux(queue<string>& que) {
    string& str = que.front();

    if(str == "nullptr") {
        que.pop();
        return nullptr;
    }

    int val = 0;
    for(char ch : str) {
        val = val*10 + ch - '0';
    }
    que.pop();

    TreeNode* node = new TreeNode(val);
    node->left = reserialize_aux(que);
    node->right = reserialize_aux(que);
    return node;
}

TreeNode* reserialize(string& series) {
    queue<string> que;
    string str;

    for(char ch : series) {
        if(ch == ',') {
            que.push(str);
            str.clear();
        }
        else {
            str += ch;
        }
    }
    
    return reserialize_aux(que);
}

TreeNode* commonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 找到了p,q或者遍历到空节点就返回
    if(root == p || root == q || root == nullptr) {
        return root;
    }
    // left和right如果不为空，就证明在该子树上找到了p或q
    TreeNode* left = commonAncestor(root->left, p, q);
    TreeNode* right = commonAncestor(root->right, p, q);

    if(left != nullptr && right != nullptr) {
        return root;    
    }
    else if(left != nullptr && right == nullptr) {
        return left;
    }
    else if(left == nullptr && right != nullptr) {
        return right;
    }
    return nullptr;
}