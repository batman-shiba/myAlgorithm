/*
最不常用算法（LFU）是一种内存置换算法，其基本思想是淘汰
最近使用频率最低（访问次数最少）的页面

为了应对短时间内某页面访问量激增的情况，算法应当定期地减少
页面的访问次数，以免过去访问量大的页面影响算法效率
*/

#include <set>
#include <list>
#include <unordered_map>
using std::set;
using std::list;
using std::unordered_map;

struct Node {
    Node(int key_, int val_, int freq_) : key(key_),
                                          value(val_),
                                          freq(freq_)
    {}

    int key, value, freq;
};

class LFUCache {
public:
    LFUCache(int capacity_) : minFreq(0), capacity(capacity_) {
        key_map.clear();
        freq_map.clear();
    }

    int get(int key) {
        if(capacity == 0) {
            return INT_MIN;
        }
        // 找到目标缓存点
        auto it = key_map.find(key);
        if(it == key_map.end()) {
            return INT_MIN;
        }
        list<Node>::iterator node = it->second;
        // 获取值和使用频率
        int val = node->value, fre = node->freq;
        // 先从原频率链表中删除
        freq_map[fre].erase(node);
        // 当前频率链表已清空，从频率哈希表中删除该组
        // 顺手更新最少频率
        if(freq_map[fre].size() == 0) {
            freq_map.erase(fre);
            if(minFreq == fre) {
                minFreq += 1;
            }
        }
        // 往新频率链表中插入修改频率后的节点，键值表也要更新
        freq_map[fre + 1].push_front(Node(key, val, fre+1));
        key_map[key] = freq_map[fre + 1].begin();

        return val;
    }

    void put(int key, int value) {
        if(capacity == 0) {
            return;
        }

        auto it = key_map.find(key);
        // 新节点
        if(it == key_map.end()) {
            // 缓存已满
            // 删除最低频率链表尾部，更新键值表
            if(key_map.size() == capacity) {
                auto itErase = freq_map[minFreq].back();
                key_map.erase(itErase.key);
                freq_map[minFreq].pop_back();

                if(freq_map[minFreq].size() == 0) {
                    freq_map.erase(minFreq);
                }
            }
            // 放入新缓存
            freq_map[1].push_front(Node(key, value, 1));
            key_map[key] = freq_map[1].begin();
            minFreq = 1;
        }
        // 旧节点
        else {
            list<Node>::iterator node = it->second;
            int fre = node->freq;
            freq_map[fre].erase(node);

            if(freq_map[fre].size() == 0) {
                freq_map.erase(fre);
                if(minFreq == fre) {
                    minFreq += 1;
                }
            }
            freq_map[fre + 1].push_front(Node(key, value, fre + 1));
            key_map[key] = freq_map[fre + 1].begin();
        }

    }

private:
    int minFreq, capacity;
    // 以键值key为索引，索引内存放的是缓存在链表中的地址
    // 主要是为了提高效率，省去遍历时间
    unordered_map<int, list<Node>::iterator> key_map; 
    
    // 以频率frequency为索引，每个索引存放一个链表，
    // 链表里存放所有频率为frequency的缓存，缓存信息有key，value和freq
    unordered_map<int, list<Node>> freq_map;
};

