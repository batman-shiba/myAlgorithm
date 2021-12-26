/*
将节点上浮以完成堆排序
*/
#ifndef _HEAP_SORT_
#define _HEAP_SORT_

#include <vector>
#include <algorithm>

using namespace std;

// 构造大顶堆
void adjustHeap(vector<int>& arr, int parent, int end) {
    int temp = arr[parent];
    
    for(int child = parent*2 + 1; child < end; child = child*2 + 1) {
        if(child + 1 < end && arr[child] < arr[child+1])
            child++;

        if(arr[child] > temp) {
            arr[parent] = arr[child];
            parent = child;
        }
        else {
            break;
        }
    }
}

void heapSort(vector<int>& arr) {
    int size = arr.size();
    
    for(int i = size / 2 - 1; i >= 0; --i) {
        adjustHeap(arr, i, size);
    }
    // 堆顶元素是数组内最大的元素，把它交换到堆底
    for(int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        adjustHeap(arr, 0, i);
    }
}

#endif /* _HEAP_SORT_ */