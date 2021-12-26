/*
参考自：https://blog.csdn.net/creatorx/article/details/71100840
AC自动机专门用于多个主串的匹配，该算法使用改良版的字典树
改善匹配过程的回溯，将时间复杂度优化到了O(n)。
当然逐一把主串与模式串做匹配也是可行的，只是会比较慢。

可以看做是在字典树上求出kmp中的next数组
*/

#ifndef _AC_AUTO_
#define _AC_AUTO_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>
using namespace std;

struct node {
    node() : fail(nullptr), cnt(0)
    {
        next.resize(26, nullptr);
    }

    node* operator= (node* other) {
        this->next = move(other->next);
        this->fail = other->fail;
        this->cnt = other->cnt;

        return this;
    }

    vector<node*> next; // 子节点  FIXME:use map to save space
    node* fail;         // 失配指针
    int cnt;            // 判断单词是否结尾
};

// 字典树
class Trie {
private:
    node* root;
    vector<node*> que;
    int head, tail;
    int strSum;

public:
    Trie() : root(new node()),  head(0), tail(0), strSum(0) 
    {}

    void insertWord(string& s) {
        node* cur = root;
        for(char& ch : s) {
            int idx = ch - 'a';
            if(cur->next[idx] == nullptr) {
                cur->next[idx] = new node();
            }
            cur = cur->next[idx];
        }
        cur->cnt++; // 表示单词结尾
        strSum += static_cast<int>(s.size());
    }

    void setFail() {
        que.resize(strSum);
        root->fail = nullptr;
        que[head++] = root;
        int idx = 0;
        while(head != tail) {
            node* temp = que[tail++];
            node* p = nullptr;

            for(idx = 0; idx < 26; ++idx) {
                if(temp->next[idx] != nullptr) {    // 实际存在的节点
                    if(temp == root) {
                        // 父节点若为root，失败指针指向root
                        temp->next[idx]->fail = root;
                    }
                    else {
                        // 回溯该节点的失败指针直到某节点的next[i]与该节点相同
                        // 把该节点的失败指针指向该next[i]节点
                        // 若回溯到root都没有找到就指向root
                        p = temp->fail;
                        while(p != nullptr) {
                            // 找到了与该节点相同的next节点
                            if(p->next[idx] != nullptr) {
                                temp->next[idx]->fail = p->next[idx];
                                break;
                            }
                            p = p->fail;
                        }
                        if(p == nullptr) {
                            temp->next[idx]->fail = root;
                        }
                    }
                    que[head++] = temp->next[idx];
                }
            }
        }
    }

    int matchTarget(string& target) {
        int idx, count = 0;
        node* p = root;
        int len = static_cast<int>(target.size());

        for(idx = 0; idx < len; ++idx) {
            int ch2int = target[idx] - 'a';
            // 由失败指针回溯查找，判断target[idx]是否在trie树上
            while(p->next[ch2int] == nullptr && p != root) {
                p = p->fail;
            }
            p = p->next[ch2int];

            if(p == nullptr)
                p = root;

            node* temp = p;
            while(temp != root) {
                assert(temp != nullptr);
                if(temp->cnt >= 0) {    // FIXME:segament fault
                    count += temp->cnt;
                    temp->cnt = -1;
                }
                else {
                    break;
                }
                temp = temp->fail;
            }
        }
        return count;
    }
};

#endif /* _AC_AUTO_ */
