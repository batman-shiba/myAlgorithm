/*
插入排序是一种稳定的排序算法
对于几乎已经排好序的数组来说，时间复杂度为O（n）
如果遇到极端情况，即原数组逆序，时间复杂度为O（n^2）
*/
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int size = arr.size();

    for(int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        // 从后往前寻找第一个小于key的位置并插入
        // 因为要给key让位置，所以元素要整体后移
        while(j >= 0 && key < arr[j]) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}