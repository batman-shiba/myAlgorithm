/*
参考自：
https://blog.csdn.net/qq_36288976/article/details/79382878
https://blog.csdn.net/qq_34374664/article/details/77488976

Tarjan算法可以用于求解有向图的强联通分量
所谓强连通分量就是两个顶点v1和v2之间，有一条v1到v2的有向路径，还有一条v2到v1的有向路径
（通俗的理解大概是v1和v2都是一个封闭图形或者说环的顶点）


各个容器的含义：
1、dfn：时间戳，标记了每个节点第一次被访问时的时间
2、low：追溯值，可以认为是一个封闭图形的根节点编号（我的理解）
3、
*/
#ifndef _TARJAN_
#define _TARJAN_

#include <string.h>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

const int kArrSize = 1001;

struct Node {
    Node() : v(0), next(0) {}
    int v, next;
};

class Tarjan {
public:
    Tarjan(vector<vector<int>>& graph);
    void init();
    void add(int x, int y);
    void tarjan(int x);
    void getResult();

private:
    int heads[kArrSize];
    int dfn[kArrSize];
    int low[kArrSize];
    bool vis[kArrSize];
    stack<int> stk;
    Node edge[kArrSize];
    int cnt, tot;

    vector<vector<int>> res;
};

// （src, pos）
Tarjan::Tarjan(vector<vector<int>>& graph) {
    init();
    int maxPoint = 0;
    for(vector<int>& v : graph) {
        add(v[0], v[1]);
        maxPoint = max(maxPoint, max(v[0], v[1]));
    }

    for(int i = 1; i <= maxPoint; ++i) {
        if(0 == dfn[i]) {
            tarjan(i);  // 这个点还没有被访问过，也就是整个图还没有遍历完
        }
    }


}

void Tarjan::init() {
    memset(heads, -1, sizeof(heads));
    memset(dfn, 0, sizeof(dfn));
    memset(low, INT_MAX, sizeof(low));
    memset(vis, false, sizeof(vis));

    tot = 0, cnt = 0;
}

void Tarjan::add(int x, int y) {
    edge[++cnt].next = heads[x];
    edge[cnt].v = y;
    heads[x] = cnt;
}

void Tarjan::tarjan(int x) { // 代表第几个点再处理
    dfn[x] = low[x] = ++tot; // 新加入的点
    stk.push(x);             // 入栈
    vis[x] = true;           // 在栈里

    for(int i = heads[x]; i != -1; i = edge[i].next) {
        if(0 == dfn[edge[i].v])  {  // 该点没访问过
            tarjan(edge[i].v);
            low[x] = min(low[x], low[edge[i].v]);
        }
        else if(vis[edge[i].v]) {  // 该点访问过，并且在栈里
            low[x] = min(low[x], dfn[edge[i].v]);
        }
    }

    vector<int> subGraph;
    if(low[x] == dfn[x]) {      // 找到了强连通分量
        int curNode = -1;
        do {
            curNode = stk.top();
            vis[curNode] = false;   // 标记出栈
            subGraph.push_back(curNode);
            stk.pop();
        }
        while(curNode != x);

        res.push_back(move(subGraph));
    }
}

void Tarjan::getResult() {
    for(auto& graph : res) {
        for(auto node : graph) {
            cout << node << " ";
        }
        cout << endl;
    }
}

#endif /* _TARJAN_ */