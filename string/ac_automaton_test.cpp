#include "AC_automaton.h"

int main() {
    Trie trie;
    int n = 0;
    cin >> n;
    string str;
    vector<string> input;
    for(int i = 0; i < n; ++i) {
        cin >> str;
        trie.insertWord(str);
    }

    string target;
    cin >> target;
    cout << trie.matchTarget(target);
    return 0;
}