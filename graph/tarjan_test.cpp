#include "Tarjan.h"

int main() {
    cout << "--------test1--------" << endl;
    vector<vector<int>> test1 = { {2,3}, {3,1}, {1,2} };
    Tarjan t1(test1);
    t1.getResult();
    cout << endl;
    
    cout << "--------test2--------" << endl;
    vector<vector<int>> test2 = { {1,2}, {3,2} };
    Tarjan t2(test2);
    t2.getResult();
    cout << endl;

    return 0;
}