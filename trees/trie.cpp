#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int M = 26;

struct Trie {
    int data;
    Trie *next[M];
    
    Trie(int data = 0) {
        this->data = data;
        for (int i = 0; i < M; i++) next[i] = NULL;
    }
    
    void add(const string &s) {
        Trie *node = this;
        for (int i = 0; i < s.length(); i++) {
            int c = s[i] - 'a';
            if (node->next[c] == NULL) {
                node->next[c] = new Trie();
            }
            node->next[c]->data++;
            node = node->next[c];
        }
    }
    
    int get(const string &s) {
        Trie *node = this;
        for (int i = 0; i < s.length(); i++) {
            int c = s[i] - 'a';
            if (node->next[c] == NULL) {
                return 0;
            }
            node = node->next[c];
        }
        return node->data;
    }
};

Trie *head = new Trie();
                
int main() {
    int q;
    string cmd, s;
    scanf(" %d ", &q);
    while (q--) {
        cin >> cmd >> s;
        if (cmd[0] == 'a') {
            head->add(s);
        } else {
            printf("%d\n", head->get(s));
        }
    }
    return 0;
}
