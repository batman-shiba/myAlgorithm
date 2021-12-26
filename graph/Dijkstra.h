/*
参考自：https://blog.csdn.net/lbperfect123/article/details/84281300

Dijkstra算法基于贪心实现，用来求有向图中的一个点到其他所有点的最短路径，
首先把起点到所有点的距离保存下来找最短，松弛一次后再找最短。
松弛操作就是把找到的

*/

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void initMatrix(vector<vector<int>>& src, vector<vector<int>>& pos) {

    for(vector<int>& threeSome : src) {
        pos[threeSome[0]][threeSome[1]] = threeSome[2];
    }

    for(int i = 0; i < pos.size(); ++i) {
        pos[i][i] = 0;
    }
}

// roads的输入格式vector里面的每一个都应该是三元组
//（源点src，目标点pos，距离distance)
vector<int> dijkstra(vector<vector<int>>& roads, int maxPointId, int start) {
    // 用来存储点到点之间的距离
    vector<vector<int>> matrix(maxPointId + 1, vector<int>(maxPointId + 1, INT_MAX));
    // 真正用来计算距离的一位数组
    vector<int> dis(maxPointId + 1, INT_MAX);
    // 标记哪些已经遍历过
    vector<bool> vis(maxPointId + 1, false);
    vis[start] = true;

    initMatrix(roads, matrix);
    dis = matrix[start];
    
    for(int i = 1; i <= maxPointId; ++i) {
        int min_ = 1e9, next = -1;
        for(int j = 1; j <= maxPointId; ++j) {
            if(!vis[j] && dis[j] < min_) {
                min_ = dis[j];
                next = j;
            }
        }

        vis[next] = true;
        
        // 松弛操作
        // 查看是否能以next为中继点找出最短路径
        // dis[j]: start->j的距离
        // dis[next] + matrix[next][j]: start->next的距离+next->j的距离
        for(int j = 1; j <= maxPointId; ++j) {
            if(matrix[next][j] + dis[next] < dis[j]) {
                dis[j] = matrix[next][j] + dis[next];
            }
        }
    }
}

// dijkstra算法是二次复杂度，并且采用邻接矩阵存储权值比较耗费内存
// 我们可以选用优先队列和邻接表优化
struct comp {
    bool operator() (pair<int, int>& p1, pair<int, int>& p2) {
        return p1.second > p2.second;
    }
};

struct mapNode {
    mapNode(int id_) : id(id_) {
        vec.clear();
    }

    int id;
    vector<pair<int, int>> vec; // pair<posid, value>，保存目标点以及权值
};


vector<int> greaterDijkstra(vector<vector<int>>& roads, int maxPointId, int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq; 
    vector<mapNode*> nodeArr(maxPointId + 1);

    vector<int> res(maxPointId + 1, 0);
    vector<bool> vis(maxPointId + 1, false);
    vis[start] = true;

    // initialize
    for(vector<int>& road : roads) {
        int src = road[0], pos = road[1], val = road[2];

        if(nodeArr[src] == nullptr) {
            nodeArr[src] = new mapNode(src);
        }

        nodeArr[src]->vec.push_back( {pos, val} );
    }

    for(pair<int, int>& pii : nodeArr[start]->vec) {
        pq.push(pii);
    }

    while(!pq.empty()) {
        const pair<int, int>& pii = pq.top();
        int id = pii.first, distance = pii.second;

        if(vis[id]) {
            pq.pop();
        }
        else {
            res[id] = distance;
            vis[id] = true;

            for(pair<int, int>& pii : nodeArr[id]->vec) {
                int pos = pii.first, posDid = pii.second;
                pq.push({pos, distance + posDid});                
            }

            pq.pop();
        }
    }

    return res;
}
