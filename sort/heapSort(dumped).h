/*
参考自：https://www.cnblogs.com/chengxiao/p/6129630.html

堆排序是利用堆进行排序的一种算法，它是一种不稳定排序
平均时间复杂度为O(nlogn)

堆是一种完全二叉树，其每个节点的值都大于或等于左右孩子节点的值，则为大顶堆，
反之则为小顶堆
定义如下：
大顶堆：arr[i] >= arr[2*i + 1] && arr[i] >= arr[2*i + 2]
小顶堆：arr[i] <= arr[2*i + 1] && arr[i] <= arr[2*i + 2]
*/

#ifndef _HEAP_SORT_
#define _HEAP_SORT_

#include <vector>
#include <iostream>
using namespace std;

class Heap {
    private:
        vector<int> arr;
        int seq;    // 决定大顶堆或是小顶堆，0是小顶堆，1是大顶堆

        // 想变换为小堆，要先成为大堆
        void adjustMinHeap(int idx, int size) {
            int temp = arr[idx];

            for(int k = idx*2 + 1; k < size; k = 2*k + 1) { // 从i的左节点开始
                // 左节点小于右节点，k指向右节点
                // 即从两个子节点中选择较大的一个
                // 然后与父节点比较大小，如果大于temp，那么把子节点的值赋给父节点
                if(k+1 < size && arr[k] < arr[k+1]) {
                    k++;
                }
                // 子节点大于父节点，将子节点的值赋给父节点
                // 当前节点下移到该子节点处
                if(arr[k] > temp) {
                    arr[idx] = arr[k];
                    idx = k;
                }
                else {
                    break;
                }
            }
            // 把一个小值下沉
            arr[idx] = temp;
        }

        // 想要变换为最大堆，需要先成为小堆
        void adjustMaxHeap(int idx, int size) {
            int temp = arr[idx];

            for(int k = idx*2 + 1; k < size; k = 2*k + 1) { // 从i的左节点开始
                // 左节点大于右节点，k指向右节点
                // 即从两个子节点中选择较小的一个
                // 然后与父节点比较大小，如果小于temp，那么把子节点的值赋给父节点
                if(k+1 < size && arr[k] > arr[k+1]) {
                    k++;
                }
                // 子节点小于父节点，将子节点的值赋给父节点
                // 当前节点下移到该子节点处
                if(arr[k] < temp) {
                    arr[idx] = arr[k];
                    idx = k;
                }
                else {
                    break;
                }
            }
            // 把一个大值下沉
            arr[idx] = temp;
        }

        void choseAdjust(int idx, int size) {
            if(0 == seq) {
                adjustMinHeap(idx, size);
                }
            else {
                adjustMaxHeap(idx, size);
            }
        }
        
    public:
        Heap(vector<int>& in) : arr(in), seq(0) {}

        vector<int> getArr() {
            return arr;
        }

        void peekSeq() {
            for(int& num : arr) {
                cout << num << " ";
            }
            cout << endl;
        }

        void changeSeq() {
            seq = (seq == 0 ? 1 : 0);
        }

        void insert(int newNum) {
            arr.push_back(newNum);
            sort();
        }

        void sort() {
            int beg = arr.size() / 2 - 1;
            int size = arr.size();
            // 使整个堆局部有序，令每个父节点都大于它的子节点
            // 从最后一个父节点开始
            for(int i = beg; i >= 0; --i) {
                choseAdjust(i, size);
            }
            // 每次遍历把头结点移动到最后（头结点是最大的），重新调整堆使头节点最大
            // 然后遍历余下的数组
            for(int i = size-1; i > 0; --i) {
                swap(arr[0], arr[i]);
                choseAdjust(0, i);
            }  
        }

};

#endif /* _HEAP_SORT_ */