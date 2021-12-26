/*
参考自：https://mp.weixin.qq.com/s/FYx3acRh9JXAIb7y97G39A
BM算法是一种非常高效的字符串匹配算法，其性能是KMP算法的3-4倍。
核心思想是模式串中某个字符与主串不能匹配时就将模式串往后滑多几位
（暴力破解是将模式串从头开始匹配，现在我们根据以下两个规则来确定模式串要滑多少位）

一、坏字符规则
模式串从后往前匹配，当某个字符没法匹配时（假设下标Si），我们把主串中的这个字符称为坏字符。
我们在模式串中从后往前找到坏字符第一次出现位置（Sj），若不存在将Sj置为-1。
此时将模式串往后移动Si-Sj位。
仅仅使用坏字符规则有可能会使模式串往前移动。

比如：
主串：  abcdefgh
模式串：abca
模式串到了第四位就不匹配了，那么就在模式串中找d这个字符，但是没找到，那么坏字符数组的第四位就设为-1。

二、好后缀规则
从后往前匹配，直到遇到不匹配的字符x，那么模式串中x之后的就是好后缀。
取模式串的各个后缀子串，找到它们在模式串中的另一匹配位置，将模式串滑到此处继续匹配。
除此之外，还要在好后缀的后缀子串中查找最长的能与模式串前缀子串匹配的后缀子串。

比如：

*/

#ifndef _BOYER_MOORE_
#define _BOYER_MOORE_

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

void getBadChar(unordered_map<char, int>& mp, string& str, int size) {
    for(int i = 0; i < size; ++i) {
        mp[str[i]] = i;
    }
}

void getGoodSuffix(vector<int>& suf, vector<bool>& pre, string& str, int size) {
    for(int i = 0; i < size-1; ++i) {
        int j = i;  // 公共后缀子串长度
        int k = 0;

        while(j >= 0 && str[j] == str[size-1-k]) {
            --j;
            ++k;
            // j+1表示公共后缀子串在[0, i]中的起始位置
            // 第j位与模式串最后一位比较开始，从后往前注意比较
            suf[k] = j+1;
        }
        // 模式串有公共的前缀-后缀串
        if(j == -1) 
            pre[k] = true;
    }
}

int moveByGoodSuf(int idx, int len, vector<int>& suf, vector<bool>& pre) {
    int k = len - 1 - idx;

    if(suf[k] != -1) {
        // 能在模式串中找到后缀子串的另一匹配串
        return idx - suf[k] + 1;
    }

    for(int r = idx+2; r < len; ++r) {
        // 是好后缀
        if(pre[len-r])
            return r;
    }
}

bool BMmatch(string& source, string& target) {
    int tLen = target.size(), sLen = source.size();
    
    vector<int> goodSuf(tLen, -1);
    vector<bool> goodPrf(tLen, false);
    unordered_map<char, int> mp;
    getGoodSuffix(goodSuf, goodPrf, target, tLen);
    getBadChar(mp, target, tLen);

    int i = 0;
    // 如果i超过了sLen - tLen就不可能找到匹配串了
    while(i <= sLen - tLen) {
        int j = 0;
        // 从后往前匹配
        for(j = tLen - 1; j >= 0; --j) {
            if(source[i+j] != target[j])
                break;
        }

        if(j < 0) {
            return true;
        }

        int badChar = j - mp[source[i+j]];
        int gSuf = 0;

        if(j < tLen-1) {
            gSuf = moveByGoodSuf(j, tLen, goodSuf, goodPrf);
        }
        // 主串滑动好后缀和坏字符规则得出距离的较大值
        i += max(badChar, gSuf);
    }
    return false;
}

#endif /* _BOYER_MOORE_ */