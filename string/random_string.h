/*
随机生成一个字符串
*/
#ifndef _RANDOM_STRING_
#define _RANDOM_STRING_

#include <string>
using namespace std;

string letters = "abcdefghijklmnopqrstuvwxyz";

string getRandomString(int len) {
    string res;

    for(int i = 0; i < len; ++i) {
        int idx = rand() % 26;
        res.push_back(letters[idx]);
    }
    return res;
}

#endif /* _RANDOM_STRING_ */