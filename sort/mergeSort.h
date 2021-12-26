/*
归并排序采用了分治的思想，把一段长数组分割成一段一段，
在局部排好序之后再merge到一起，
时间复杂度O(nlogn)
*/
#ifndef _MERGE_SORT_
#define _MERGE_SORT_

#include <vector>
#include <limits.h>
using std::vector;

void Merge(vector<int>& out, int l, int mid, int r) {
    int idxLeft = 0, idxRight = 0;
    // 创建两个辅助数组，以便进行排序
    vector<int> leftArray(out.begin() + l, out.begin() + mid + 1);
    vector<int> rightArray(out.begin() + mid + 1, out.begin() + r + 1);
    // 辅助数组尾部插入一个极大值，避免下标越界
    leftArray.push_back(INT_MAX);
    rightArray.push_back(INT_MAX);

    for(int i = l; i <= r; ++i) {
        // 左数组指针所指的值较小，就排在前面
        if(leftArray[idxLeft] < rightArray[idxRight]) {
            out[i] = leftArray[idxLeft];
            idxLeft++;
        }
        else {
            out[i] = rightArray[idxRight];
            idxRight++;
        }
    }
}

void mergeSort_aux(vector<int>& output, int beg, int end) {
    if(beg >= end) {
        return;
    }

    int mid = (beg + end) >> 1;
    
    mergeSort_aux(output, beg, mid);
    mergeSort_aux(output, mid+1, end);
    Merge(output, beg, mid, end);
}

void mergeSort(vector<int>& arr) {
    int beg = 0, end = arr.size() - 1;
    mergeSort_aux(arr, beg, end);
}

#endif /* _MERGE_SORT_ */