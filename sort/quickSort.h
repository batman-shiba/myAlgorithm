/*
快速排序的时间复杂度比较稳定，平均时间复杂度为O（nlogn）
快速排序采用分治思想，在一个子区间内去一个pivot作为标准值，
比pivot小的放前面，比pivot大的放后面。
pivot的值的选择很重要，可以在子区间的头、中、尾
各取一个值再去平均作为pivot
快速排序是最快的排序算法之一，标准库里的sort实现也是使用
快排，但是面对庞大的数据量时，快排的递归层数太多，因此
标准库在快排的递归层数大于20层时会退而使用堆排序。
*/

#include <vector>
using namespace std;

int splice(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    while(low < high) {
        // 在数组右方找到小于pivot的值
        while(low < high && arr[high] >= pivot) {
            --high;
        }
        // 小值赋给低位
        arr[low] = arr[high];
        // 在数组左方找到大于pivot的值
        while(low < high && arr[low] <= pivot) {
            ++low;
        }
        // 大值赋给高位
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void quickSort_aux(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pivot = splice(arr, low, high);

        quickSort_aux(arr, low, pivot - 1);
        quickSort_aux(arr, pivot + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;

    quickSort_aux(arr, low, high);
}