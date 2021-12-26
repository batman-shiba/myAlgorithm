/*
二叉搜索树是一种查询效率很高的数据结构，最慢需要O（logn）
每个节点的值都大于左子树节点，都小于右子树节点
*/
#ifndef _BST_
#define _BST_

#include "../treeNode.h"
#include <vector>
#include <algorithm>
using namespace std;

// 设计的并不好，也就看个乐
class BST {
    private:
        TreeNode* root;

        TreeNode* buildBST(vector<int>& arr, int low, int high) {
            if(low > high) {
                return nullptr;
            }

            int mid = (low + high) >> 1;
            TreeNode* newNode = new TreeNode(arr[mid]);
            newNode->left = buildBST(arr, low, mid - 1);
            newNode->right = buildBST(arr, mid + 1, high);
            
            return newNode;
        }

        TreeNode* remove_aux(TreeNode* node, int num, bool& modify) {
            if(node == nullptr) {
                return nullptr;
            }
    
            if(node->val > num) {
                node->left = remove_aux(node->left, num, modify);
            }
            else if(node->val < num) {
                node->right = remove_aux(node->right, num, modify);
            }
            else {
                modify = true;
                TreeNode* l = node->left;

                if(node->right == nullptr) {
                    delete node;
                    return l;
                }
                else {
                    TreeNode* ret = node->right;
                    TreeNode* temp = ret;

                    while(temp->left != nullptr) {
                        temp = temp->left;
                    }

                    temp->left = l;
                    delete node;
                    return ret;
                }
            }
            return node;
        }

    public:
        BST() : root() {}

        void init(vector<int>& arr) {
            sort(arr.begin(), arr.end());
            root = buildBST(arr, 0, static_cast<int>(arr.size()) - 1);
        }

        TreeNode* getRoot() {
            return root;
        }

        bool insert(int num) {
            TreeNode* pre = nullptr;
            TreeNode* cur = root;

            while(cur != nullptr) {
                if(cur->val > num) {
                    pre = cur;
                    cur = cur->left;
                }
                else if(cur->val < num) {
                    pre = cur;
                    cur = cur->right;
                }
                else {
                    return false;
                }
            }

            if(pre->val > num) {
                pre->left = new TreeNode(num);
            }
            else {
                pre->right = new TreeNode(num);
            }

            return true;
        }

        bool remove(int num) {
            bool isModify = false;
            remove_aux(root, num, isModify);

            return isModify;
        }
};

#endif /* _BST_ */