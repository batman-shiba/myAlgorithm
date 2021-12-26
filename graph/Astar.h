/*
参考自：https://blog.csdn.net/nie2314550441/article/details/106733189

A*算法是常用的路径查找和图形遍历算法，是dijkstra算法的扩展
用于在静态网格中寻找起点与终点的最短距离的算法
本质上是将BFS和DFS两种思想糅合在一起
*/

#ifndef _ASTAR_
#define _ASTAR_

#include <assert.h>
#include <vector>
#include <list>
#include <queue>

using namespace std;

// 封装矩阵上一点的横纵坐标以及访问标记
// 重载-号，用于计算两点之间的曼哈顿距离，即欧式距离在横轴和纵轴上的投影相加而得的距离
// 具体可看：https://blog.csdn.net/hermito/article/details/40989589
struct Point
{
    int x, y; // x y坐标
    bool vis; // 是否访问过
    Point(int tx = 0, int ty = 0) : y(tx), x(ty), 
                                    vis(false)
    {}

    void operator= (const Point* other) {
        this->y = other->y;
        this->x = other->x;
        this->vis = other->vis;
    }
    // 曼哈顿距离
    int operator- (const Point& other) {
        return abs(y - other.y) + abs(x - other.x);
    }

    bool operator== (const Point& other) {
        return y == other.y && x == other.x;
    }
};

// 对Point结构体的进一步封装，为了估价思想而生
// 代价g是起点到指定方格的移动代价（直行10，对角线移动14）
// 代价h是从指定方格移动到终点的代价（曼哈顿距离）
// 代价f是g和h之和
struct PointStar
{
    int f, g, h;
    Point* parentPoint;
    Point* thePoint;

    PointStar(int tf, int tg, int th, int px, int py) : f(tf), g(tg), h(th),
                                                        parentPoint(nullptr),
                                                        thePoint(new Point(px, py))
    {}

    void operator= (PointStar* other) {
        this->f = other->f;
        this->g = other->g;
        this->h = other->h;
        this->parentPoint = other->parentPoint;
        this->thePoint = other->thePoint;
    }

    bool operator> (const PointStar& other) {
        return f > other.f;
    }

    void setParentPoint(Point* other)
    { parentPoint = other; }

    void setF(int f_)
    { f = f_; }

    void setG(int g_)
    { g = g_; }

    void setH(int h_)
    { h = h_; }

    void setPointTrue()
    { this->thePoint->vis = true; }

    bool isVisited()
    { return this->thePoint->vis; }
};

struct comp
{
    bool operator() (PointStar* pa, PointStar* pb)
    {
        return pa > pb;   // 小顶堆
    }
};


// 八个方向的横纵坐标变换以及相应的代价
// 水平或者上下前进一个的代价是10，左上右上等对角线的方向代价是14（根号2乘10并取整）
vector<int> dx = {-1, 0, 1, -1, 1, -1, 0, 1};
vector<int> dy = {-1, -1, -1, 0, 0, 1, 1, 1};
vector<int> dval = {14, 10, 14, 10, 10, 14, 10, 14};

bool moveable(int x_, int y_, int heightLimit, int midthLimit) {
    if(x_ < 0 || x_ >= heightLimit || y_ < 0 || y_ >= midthLimit) {
        return false;
    }
    return true;
}


// 0是可通行的，1是障碍物
bool Astar(vector<vector<int>>& matrix, Point* start, Point* end) {
    if(matrix.empty() || start == end)
        return false;

    int matrixHeight = static_cast<int>( matrix.size() );
    int matrixmidth = static_cast<int>( matrix[0].size() );

    // 起点或者终点是障碍物
    if(matrix[start->x][start->y] != 0 || matrix[end->x][end->y] != 0)
        return false;
    // 起点或终点超出矩阵大小
    if(start->y > matrixmidth || start->x > matrixHeight || 
       end->y > matrixmidth || end->x > matrixHeight) 
        return false;

    vector<vector<PointStar*>> pstarArr(matrixHeight + 1, vector<PointStar*>(matrixmidth + 1)); // 保存代价点
    priority_queue<PointStar, vector<PointStar>, comp> pstarPriQue;     // 堆顶是代价最小的点

    int g_ = 0, h_ = (start - end) * 10, f_ = g_ + h_;
    PointStar* pt = new PointStar(f_, g_, h_, start->x, start->y);
    pt->setPointTrue();
    pstarArr[start->x][start->y] = pt;
    pstarPriQue.push(*pt);

    bool seeking = true;

    while(seeking && !pstarPriQue.empty()) {
        PointStar temp = pstarPriQue.top();
        pstarPriQue.pop();

        for(int i = 0; i < dx.size() && seeking; ++i) {
            // 遍历上下左右以及对角线八个方向的点
            Point* t = new Point(temp.h + dx[i], temp.h + dy[i]);

            if( !moveable(t->x, t->y, matrixHeight, matrixmidth) )
                continue;
            // 
            if(matrix[t->x][t->y] == 1 || pstarArr[t->x][t->y]->isVisited())
                continue;
            // 估算代价1
            g_ = temp.g + dval[i];
            h_ = (t - end) * 10;
            f_ = g_ + h_;

            int minf = f_;

            PointStar* newPstar = new PointStar(f_, g_, h_, t->x, t->y);
            newPstar->setPointTrue();
            newPstar->setParentPoint(t);

            for(int j = 0; j < dx.size(); ++j) {
                Point* tj = new Point(t->x + dx[j], t->y + dy[j]);

                if( !moveable(tj->x, tj->y, matrixHeight, matrixmidth) )
                    continue;
                // 这里需要父节点已被访问
                if(matrix[tj->x][tj->y] == 1 || !pstarArr[tj->x][tj->y]->isVisited())
                    continue;
                // 更新代价
                g_ = pstarArr[tj->x][tj->y]->g + dval[j];
                f_ = g_ + h_;

                if(f_ <= minf) {
                    minf = f_;
                    
                    newPstar->setF(f_);
                    newPstar->setG(g_);
                    newPstar->setH(h_);
                    newPstar->setParentPoint(tj);
                }
            }

            pstarArr[t->x][t->y] = newPstar;    
            pstarPriQue.push(*pstarArr[t->x][t->y]);

            if(t == end) {
                seeking = false;
            }
        }
    }
    return true;
}

#endif /* _ASTAR_ */