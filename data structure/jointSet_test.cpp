#include "Disjoint-Set.h"

int main() {
    vector<vector<int>> test = { {3,1}, {1,4}, {3, 4} };
    DjointSet ds(test);

    ds.showGroup();
    return 0;
}