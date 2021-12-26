#include <vector>
#include <stdlib.h>
using namespace std;

vector<int> getRandomArray(int size, int limit) {
    vector<int> temp;

    for(int i = 0; i < size; ++i) {
        int num = rand() % limit;
        temp.push_back(num);
    }
    return temp;
}