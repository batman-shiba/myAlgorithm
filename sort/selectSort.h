/*
选择排序，就是遍历数组并找出最小的值，与数组未排序部分
的第一个数组交换
*/
#ifndef _SELECT_SORT_
#define _SELECT_SORT_

#include <vector>
#include <math.h>
using namespace std;

void selectSort(vector<int>& arr) {
    int minIdx = -1;
    int minNum = INT_MAX;
    int size = arr.size();

    for(int i = 0; i < size - 1; ++i) {
        minNum = INT_MAX;
        
        for(int j = i; j < size; ++j) {
            if(arr[j] < minNum) {
                minNum = arr[j];
                minIdx = j;
            }
        }
        
        swap(arr[i], arr[minIdx]);
    }
}

#endif /* _SELECT_SORT_ */