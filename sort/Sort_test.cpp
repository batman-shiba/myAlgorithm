#include "quickSort.h"
#include "heapSort.h"
#include "insertionSort.h"
#include "mergeSort.h"
#include "radioSort.h"
#include "selectSort.h"
#include "shellSort.h"
#include "mergeSort.h"
#include "random_array.h"
#include <time.h>
#include <iostream>

void printfVec(vector<int>& arr) {
    for(int& num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    srand(clock());
    int size = 200000, limit = 1e9;
    clock_t t1,t2;
    vector<int> test = getRandomArray(size, limit);
    vector<int> base = test;
    
    cout << "----quicksort----" << endl;
    t1 = clock();
    quickSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;
    //printfVec(test);
    test = base;

    cout << "----insertionsort----" << endl;
    t1 = clock();
    insertionSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;
    //printfVec(test);
    test = base;

    cout << "----mergesort----" << endl;
    t1 = clock();
    mergeSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;
    //printfVec(test);
    test = base;

    cout << "----radiosort----" << endl;
    t1 = clock();
    radioSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;
    //printfVec(test);
    test = base;

    cout << "----selectsort----" << endl;
    t1 = clock();
    selectSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;
    //printfVec(test);
    test = base;

    cout << "----shellsort----" << endl;
    t1 = clock();
    shellSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;
    //printfVec(test);
    test = base;

    cout << "----heapsort----" << endl;
    t1 = clock();
    heapSort(test);
    t2 = clock();
    cout << t2 - t1 << endl;

    return 0;
}