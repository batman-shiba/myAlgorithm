//#include "kmp.h"
//#include "Boyer-Moore.h"
#include "random_string.h"
#include <time.h>
#include <iostream>

int main() {
    srand(clock());
    string s1 = "abdsajlaskdmcdsaiuoqdjkalsjdalskdsjalczxndasjkyduiyddhjkashdadk";
    string s2 = "jka";
    cout << s1 << endl;
    cout << s2 << endl;
    clock_t c1 = clock();
    //cout << BMmatch(s1, s2) << endl;
    clock_t c2 = clock();

    cout << "timediff = " << (c2 - c1) << endl; 

    return 0;
}
