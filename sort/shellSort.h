/*
插入排序的变种
先让数组中任意间隔为d的元素有序，逐渐把d缩小
直到d=1，就意味着数组内任意两个相邻元素都有序
*/
#ifndef _SHELL_SORT_
#define _SHELL_SORT_

#include <vector>
using namespace std;

void insert(vector<int>& arr, int start, int step) {
    int temp = arr[start];
    int k;    
    for(k = start - step; k >= 0 && temp < arr[k]; k -= step) {
        arr[k + step] = arr[k];
    }
    arr[k + step] = temp;
}

void shellSort(vector<int>& arr) {
    int size = arr.size();

    // 调整步长，每次都减半
    for(int step = size/2; step > 0; step /=2) {
        // 分组进行插入排序
        for(int i = step; i < size; ++i) {
            insert(arr, i, step);
        }
    }
}

#endif /* _SHELL_SORT_ */