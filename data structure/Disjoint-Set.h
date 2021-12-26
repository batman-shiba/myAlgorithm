/*
参考自：《算法竞赛进阶指南》并查集一节

并查集可以动态维护若干个不重叠的集合。
我们从每个集合中选出一个代表元素，把这个集合的所有元素
的编号都换成代表元素的编号

并查集实则是一个森林（每一个集合都是一棵树）
由于普通的树的深度可能会很大，为了提高效率，并查集使用了路径压缩
让根节点的所有子节点全部指向根节点
*/
#ifndef _JOINT_SET_
#define _JOINT_SET_

#include <math.h>
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class DjointSet {
public:
    DjointSet(vector<vector<int>>& arr);    // (parent, child)

    int howmanyGroup();
    bool isInOneSet(int x, int y);
    void showGroup();

private:
    int get(int x);
    void merge(int x, int y);
    void init(vector<vector<int>>& arr);

    vector<int> theSet;
    vector<vector<int>> groupSet;
    int groups_;
};

DjointSet::DjointSet(vector<vector<int>>& arr) {
    groups_ = 0;
    int size = arr.size();
    int maxPoint = 0;
    
    for(vector<int>& v : arr) {
        maxPoint = std::max(maxPoint, std::max(v[0], v[1]));
    }

    theSet.resize(maxPoint + 1, 0);
    groupSet.resize(maxPoint + 1);

    for(int i = 0; i <= maxPoint; ++i) {
        theSet[i] = i;
    }

    for(vector<int>& v : arr) {
        merge(v[0], v[1]);
    }

    for(int i = 0; i <= maxPoint; ++i) {
        if(theSet[i] == i) {
            groups_++;
        }
        groupSet[theSet[i]].push_back(i);    
    }
}

int DjointSet::howmanyGroup() {
    return groups_;
}

bool DjointSet::isInOneSet(int x, int y) {
    return theSet[x] == theSet[y];
}

int DjointSet::get(int x) {             // 只有根节点才会出现x == theSet[x]
    if(x != theSet[x]) {                // 因此get的过程就是不断寻找父节点直到找到根节点的过程
        x = get(theSet[x]);
    }

    return x;
}

void DjointSet::merge(int x, int y) {   // 合并
    int prex = get(x), prey = get(y);
    if(prex >= prey) {
        theSet[prey] = prey;
    }
    else {
        theSet[prex] = prey;
    }
}

void DjointSet::showGroup() {

    for(auto& vec : groupSet) {
        if(vec.size() < 2)
            continue;

        for(auto& val : vec) {
            cout << val << " ";
        }
        cout << endl;
    }
}


#endif /* _JOINT_SET_ */