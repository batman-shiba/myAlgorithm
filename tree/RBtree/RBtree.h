/*
参考自：https://github.com/softpudding/someSimpleAlgorithms/blob/master/redBlackTree/rbtree.h
红黑树是一种特殊的二叉搜索树，每个节点新增了颜色标记（红色或黑色）
有以下特征：
1、根节点是黑色的
2、如果一个节点为红色，它的子节点一定是黑色(充分不必要条件)
3、叶的子节点是黑色（叶的左右子节点都为空，都认为是黑色）
4、没有一条路径会比其他路径长一倍
*/
#ifndef _RBTREE_
#define _RBTREE_

#include <queue>
#include <string>
#include <iostream>

using std::string;
using std::queue;
using std::cout;
using std::endl;

enum Color{kRED, kBALCK};

struct RBNode {
    RBNode(int key_) : key(key_), color(kRED), 
                       left(nullptr), right(nullptr),
                       parent(nullptr)
    {}

    RBNode* operator=(RBNode* node) {
        color = node->color;
        key = node->key;
        left = node->left;
        right = node->right;
        parent = node->parent;
    }

    bool isRed()
    { return color == kRED; }

    void turnRed()
    { color = kRED; }

    void turnBlack()
    { color = kBALCK; }

    void setColor(RBNode* other)
    { color = other->color; }

    RBNode* getParent()
    { return this->parent; }

    Color color;
    int key;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
};

typedef RBNode rbNode;

class RBTree {
public:
    void peekTree();
    rbNode* insert(int val);
    bool remove(int val);

private:
    void swapTrees(rbNode* node1, rbNode* node2);
    void leftRotate(rbNode* node);
    void rightRotate(rbNode* node);
    void insertFixup(rbNode* node);
    void removeFixup(rbNode* node);
    rbNode* search(int key);
    rbNode* predecessorNode(rbNode* node); // 前继节点
    rbNode* successor(rbNode* node);       // 后继节点

    rbNode* root;
};

#endif /* _RBTREE_ */