/*
基数排序沿袭了桶排序的思想，从数字的最低位开始分桶
*/

#ifndef _RADIO_SORT_
#define _RADIO_SORT_

#include <math.h>
#include <vector>
#include <queue>
using namespace std;

// 只考虑正数
// 如果考虑负数，要扩充桶的数量并且要把下标进行映射
void radioSort(vector<int>& arr) {
    vector<queue<int>> buckets(10);
    
    int mostBitsNum = 0;
    int maxNum = 0;
    for(int& num : arr) {
        maxNum = max(num, maxNum);
    }

    while(maxNum > 0) {
        mostBitsNum++;
        maxNum /= 10;
    }

    for(int i = 1; i <= mostBitsNum; ++i) {
        
        for(int& num : arr) {
            int bucketIdx = ( num / static_cast<int>(pow(10, i - 1)) ) % 10;
            buckets[bucketIdx].push(num);
        }
        
        int idx = 0;
        for(int i = 0; i < 10; ++i) {

            while(!buckets[i].empty()) {
                arr[idx] = buckets[i].front();
                buckets[i].pop();
                ++idx;
            }
        }
    }
}

#endif /* _RADIO_SORT_ */

