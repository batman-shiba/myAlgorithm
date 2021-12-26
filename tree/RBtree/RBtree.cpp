#include "RBtree.h"

// 序列化整棵树
void RBTree::peekTree() {
    rbNode* node = root;
    queue<rbNode*> que;
    que.push(node);

    while(!que.empty()) {
        string color = (node->isRed() ? "red" : "black");
        node = que.front();
        que.pop();

        if(node == nullptr) {
            cout << "nullptr, ";
        }
        else {
            cout << std::to_string(node->key) << "(" << color << "), ";
            que.push(node->left);
            que.push(node->right);
        }
    }
}

rbNode* RBTree::search(int key) {
    rbNode* node = root;

    while(node != nullptr) {
        if(key < node->key) {
            node = node->left;
        }
        else if(key > node->key) {
            node = node->right;
        }
        else {
            return node;
        }
    }
    return nullptr;
}

// 如果在当前子树下找不到前继或后继节点就返回父节点
rbNode* RBTree::predecessorNode(rbNode* node) {
    rbNode* cur = node;

    if(node->left == nullptr) {
        return node->parent;
    }

    cur = cur->left;
    while(cur->right != nullptr) {
        cur = cur->right;
    }

    return cur;
}

rbNode* RBTree::successor(rbNode* node) {
    rbNode* cur = node;

    if(node->right == nullptr) {
        return node->parent;
    }

    cur = cur->right;
    while(cur->left != nullptr) {
        cur = cur->left;
    }

    return cur;
}

void RBTree::swapTrees(rbNode* node1, rbNode* node2) {
    rbNode* pre = node1->parent;

    if(pre != nullptr) {
        if(node1 == pre->left) {
            pre->left = node2;
        }
        else {
            pre->right = node2;
        }
    }
    else {
        root = node2;
    }
}

void RBTree::leftRotate(rbNode* node) {
    if(node == root) {
        root = node->left;
    }

    rbNode* r = node->right;
    node->right = r->left;
    r->left->parent = node;
    r->parent = node->parent;
    r->left = node;

    rbNode* pre = node->parent;
    if(pre != nullptr) {
        if(node == node->parent->right) {
            node->parent->right = r;
        }
        else {
            node->parent->left = r;
        }
    }

    node->parent = r;
}

void RBTree::rightRotate(rbNode* node) {
    if(node == root) {
        root = node->right;
    }

    rbNode* l = node->left;
    node->left = l->right;
    l->right->parent = node;
    l->parent = node->parent;
    l->right = node;

    rbNode* pre = node->parent;
    if(pre != nullptr) {
        if(node == node->parent->right) {
            node->parent->right = l;
        }
        else {
            node->parent->left = l;
        }
    }

    node->parent = l;
}

rbNode* RBTree::insert(int key) {
    if(root == nullptr) {
        root = new rbNode(key);
        return root;
    }

    rbNode* cur = root;
    rbNode* pre = nullptr;

    while(cur != nullptr) {
        pre = cur;
        if(key < cur->key) {
            cur = cur->left;
        }
        else if(key > cur->key) {
            cur = cur->right;
        }
        else {
            cout << key << "is in tree" << endl;
            return nullptr;
        }
    }

    rbNode* newNode = new rbNode(key);
    if(key < pre->key) {
        pre->left = newNode;
        pre->left->parent = pre;
        pre->left->turnRed();

        insertFixup(pre->left);
    }
    else {
        pre->right = newNode;
        pre->right->parent = pre;
        pre->right->turnRed();

        insertFixup(pre->right);
    }
    return newNode;
}

void RBTree::insertFixup(rbNode* node) {
    if(root == node) {
        return;
    }

    if(node->parent == nullptr) {
        return;
    }

    while(node->parent->isRed()) {
        rbNode* grandPre = node->parent->parent;
        if(grandPre == nullptr) {
            return;
        }

        if(node->parent == grandPre->left) {
            rbNode* uncle = grandPre->right;
            if(uncle == nullptr) {
                return;
            }

            if(uncle->isRed()) {
                node->parent->turnBlack();
                uncle->turnBlack();
                grandPre->turnRed();
                node = grandPre;
            }
            else if(!uncle->isRed() && node == node->parent->right) {
                node = node->parent;
                leftRotate(node);
            }
            else if(!uncle->isRed() && node == node->parent->left) {
                node->parent->turnBlack();
                grandPre->turnRed();
                rightRotate(grandPre);
            }
        }
        else {
            rbNode* uncle = node->parent->parent->left;
            if(uncle == nullptr) {
                return;
            }

            if(uncle->isRed()) {
                node->parent->turnBlack();
                uncle->turnBlack();
                grandPre->turnRed();
                node = grandPre;
            }
            else if(!uncle->isRed() && node == node->parent->left) {
                node = node->parent;
                rightRotate(node);
            }
            else if(!uncle->isRed() && node == node->parent->right) {
                node->parent->turnBlack();
                grandPre->turnRed();
                leftRotate(grandPre);
            }
        }
    }
    root->turnBlack();
}

bool RBTree::remove(int key) {
    rbNode* toRemove = search(key);
    rbNode* replace = toRemove;
    rbNode* fix;
    Color original_color = toRemove->color;

    if(toRemove->left == nullptr) {
        fix = toRemove->right;
        swapTrees(toRemove, toRemove->right);
    }
    else if(toRemove->right == nullptr) {
        fix = toRemove->left;
        swapTrees(toRemove, toRemove->left);
    }
    else {
        replace = successor(toRemove);
        original_color = replace->color;
        fix = toRemove->right;

        if(replace->parent == toRemove) {
            swapTrees(toRemove, replace);
            replace->left = toRemove->left;
            toRemove->left->parent = replace;
            replace->setColor(toRemove);
        }
        else {
            swapTrees(replace, replace->right);
            replace->left = toRemove->left;
            toRemove->left->parent = replace;
            replace->right = toRemove->right;
            toRemove->right->parent = replace;
            swapTrees(toRemove, replace);
        }
    }
    if(original_color == kBALCK)
        removeFixup(fix);
}

void RBTree::removeFixup(rbNode* node) {
    while(!node->isRed() && node != root) {
        if(node == node->parent->left) {
            rbNode* bro = node->parent->right;

            if(bro->isRed()) {
                node->parent->turnRed();
                bro->turnBlack();
                leftRotate(node->parent);
                bro = node->parent->right;
            }
            else if(bro->left != nullptr && !bro->left->isRed() &&
                    bro->right != nullptr && !bro->right->isRed())
            {
                node->parent->turnRed();
                node = node->parent;
            }
            else if(!bro->isRed() && 
                    bro->left != nullptr && bro->left->isRed())
            {
                bro->turnRed();
                bro->left->turnBlack();
                rightRotate(bro);
            }
            else if(bro->right != nullptr && bro->right->isRed())
            {
                bro->right->turnBlack();
                bro->setColor(node->parent);
                node->parent->turnBlack();
                leftRotate(node->parent);
                node = root;
            }
        }
        else {
            rbNode* bro = node->parent->left;

            if(bro->isRed()) {
                node->parent->turnRed();
                bro->turnBlack();
                rightRotate(node->parent);
                bro = node->parent->left;
            }
            else if(bro->left != nullptr && !bro->left->isRed() &&
                    bro->right != nullptr && !bro->right->isRed())
            {
                node->parent->turnRed();
                node = node->parent;
            }
            else if(!bro->isRed() && 
                    bro->left != nullptr && bro->right->isRed())
            {
                bro->turnRed();
                bro->right->turnBlack();
                leftRotate(bro);
            }
            else if(bro->left != nullptr && bro->left->isRed())
            {
                bro->left->turnBlack();
                bro->setColor(node->parent);
                node->parent->turnBlack();
                rightRotate(node->parent);
                node = root;
            }
        }
    }
    node->turnBlack();
}