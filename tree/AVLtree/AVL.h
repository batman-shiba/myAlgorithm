/*
参考自：https://www.cnblogs.com/skywang12345/p/3576969.html#aa1
二叉搜索树虽然有很好的查询效率，但是没有自平衡能力
如果顺序插入数字1-9，二叉树就会退化成链表，那么查询时间就降低为线性复杂度
因此引入AVL树，来实现自平衡平衡功能，使得整个树
尽量变成平衡二叉树（每个节点的左右子树的高度差不超过1）
 ___________________
|                   |
|                   |
|___________________|

*/

#ifndef _AVL_
#define _AVL_
#include <vector>
#include <math.h>
#include <queue>
#include <iostream>

using std::max;
using std::vector;
using std::queue;
using std::cout;
using std::endl;

struct AVLNode {
    AVLNode(int key_) : key(key_), height(0),left(nullptr), right(nullptr) {}

    AVLNode* operator=(AVLNode* other) {
        this->key = other->key;
        this->height = other->height;
        this->left = other->left;
        this->right = other->right;

        return this;
    }

    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
};

typedef AVLNode avlNode;

class AVL {
private:
    int getHeight(avlNode* node)
    { return node == nullptr ? 0 : node->height; }

    void updateHeight(avlNode* node)
    { node->height = max(getHeight(node->left), getHeight(node->right)) + 1; }

    avlNode* insert_node_aux(avlNode* start, int val);
    avlNode* erase_node_aux(avlNode* start, avlNode* pos);
    // 插入或删除一个节点后，可能会发生下列四种情况
    avlNode* LLrotate(avlNode* node); // 左子树的左子树有非空节点，导致左子树高度比右子树大2
    avlNode* RRrotate(avlNode* node); // 右子树的右子树有非空节点，导致右子树高度比左子树大2
    avlNode* LRrotate(avlNode* node); // 左子树的右子树有非空节点，导致左子树高度比右子树大2
    avlNode* RLrotate(avlNode* node); // 右子树的左子树有非空节点，导致右子树高度比左子树大2
    avlNode* root = nullptr;

public:
    void init(std::vector<int>& arr);
    void peekTree();
    avlNode* insert_node(int val);
    avlNode* erase_node(int val);
    avlNode* getRoot()
    { return root; }
};

void AVL::init(vector<int>& arr) {
    int size = arr.size();
    if(size < 1) {
        return;
    }

    root = insert_node_aux(nullptr, arr[0]);
    for(int i = 1; i < size; ++i) {
        root = insert_node_aux(root, arr[i]);
    }
}

void AVL::peekTree() {
    queue<AVLNode*> que;
    que.push(root);
    AVLNode* node = root;

    while(!que.empty()) {
        node = que.front();
        que.pop();

        if(node == nullptr) {
            cout << "nullptr, ";
        }
        else {
            cout << std::to_string(node->key) << ", ";
            que.push(node->left);
            que.push(node->right);
        }
    }
    cout << endl;
}

avlNode* AVL::insert_node_aux(avlNode* node, int key) {
    if(node == nullptr) {
        return new avlNode(key);
    }
    
    if(key < node->key) {
        node->left = insert_node_aux(node->left, key);
        
        if( getHeight(node->left) - getHeight(node->right) == 2) {
            // key放到了node的左子树的左节点
            if(key < node->left->key) {
                node = LLrotate(node);
            }
            // key放到了左子树右节点
            else {
                node = LRrotate(node);
            }
        } 
    }
    else if(key > node->key) {
        node->right = insert_node_aux(node->right, key);

        if( getHeight(node->right) - getHeight(node->left) == 2) {
            if(key > node->right->key) {
                node = RRrotate(node);
            }
            else {
                node = RLrotate(node);
            }
        }
    }

    updateHeight(node);
    return node;
}

avlNode* AVL::insert_node(int key) {
    return insert_node_aux(root, key);
}

avlNode* AVL::erase_node(int key) {
    AVLNode* node = root;

    while(node != nullptr) {
        if(node->key > key) {
            node = node->left;
        }
        else if(node->key < key) {
            node = node->right;
        }
        else {
            root = erase_node_aux(root, node);
            break;
        }
    }
    return root;
}

avlNode* AVL::erase_node_aux(avlNode* node, avlNode* pos) {
    if(pos->key < node->key) {
        node->left = erase_node_aux(node->left, pos);
        // 由于删除了左子树的某个节点，因此右子树可能会高于左子树
        if( getHeight(node->right) - getHeight(node->left) == 2) {
            avlNode* right_child = node->right;
            
            if( getHeight(right_child->left) > getHeight(right_child->right) ) {
                node = RLrotate(node);
            }
            else {
                node = RRrotate(node);
            }
        } 
    }
    else if(pos->key > node->key) {
        node->right = erase_node_aux(node->right, pos);
        // 由于删除了右子树的某个节点，所以左子树可能高于右子树
        if( getHeight(node->left) - getHeight(node->right) == 2) {
            avlNode* left_child = node->left;

            if( getHeight(left_child->right) > getHeight(left_child->left) ) {
                node = LRrotate(node);
            }
            else {
                node = LLrotate(node);
            }
        }
    }
    else { // 找到了要删除的节点，也就是node == pos
        // 左右孩子都不为空   
        if((node->left != nullptr) && (node->right != nullptr)) {
             // 如果左子树比较高，应该找左子树的最大节点，把它的值赋给当前节点，然后将其删除
            if( getHeight(node->left) > getHeight(node->right) ) {
                avlNode* temp = node->left;
                while(temp->right != nullptr) {
                    temp = temp->right;
                }

                node->key = temp->key;
                node->left = erase_node_aux(node->left, temp);
            }
            // 如果左右子树都一样高或者右子树比左子树高1
            // 就应该找出右子树的最小节点，把它的值赋给当前节点，然后将其删除
            else {
                avlNode* temp = node->right;
                while(temp->left != nullptr) {
                    temp = temp->left;
                }

                node->key = temp->key;
                node->right = erase_node_aux(node->right, temp);
            }
        }
        // 左子树或右子树为空
        else {
            avlNode* temp = node;
            node = (node->left == nullptr ? node->right : node->left);
            delete(temp);
        }
    }
    return node;
}

avlNode* AVL::LLrotate(avlNode* node) {
    avlNode* left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;

    updateHeight(node);
    updateHeight(left_child);

    return left_child;
}

avlNode* AVL::RRrotate(avlNode* node) {
    avlNode* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;

    updateHeight(node);
    updateHeight(right_child);

    return right_child;
}

avlNode* AVL::LRrotate(avlNode* node) {
    node->left = RRrotate(node->left);

    return LLrotate(node);
}

avlNode* AVL::RLrotate(avlNode* node) {
    node->right = LLrotate(node->right);

    return RRrotate(node);
}

#endif /* _AVL_ */