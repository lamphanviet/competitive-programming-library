#include <bits/stdc++.h>

using namespace std;

#define fr(i,a,b) for (int i = (a), _b = (b); i <= _b; i++)
#define frr(i,a,b) for (int i = (a), _b = (b); i >= _b; i--)
#define rep(i,n) for (int i = 0, _n = (n); i < _n; i++)
#define repr(i,n) for (int i = (n) - 1; i >= 0; i--)

// Test problem: http://codeforces.com/contest/916/problem/D
const int MAX_CHILDS = 26;
struct StringTrie {
    StringTrie *child[MAX_CHILDS];
    int dat;

    StringTrie() {
        rep(i, MAX_CHILDS) child[i] = NULL;
        dat = -1;
    }

    StringTrie(StringTrie *node) {
        rep(i, MAX_CHILDS) child[i] = node->child[i];
        dat = node->dat;
    }

    // the string consist of only lower case letters [a-z]
    StringTrie *set(string &s, int val, int pos = 0) {
        StringTrie *node = new StringTrie(this);
        if (pos >= s.size()) {
            node->dat = val;
        } else {
            int v = s[pos] - 'a';
            if (!child[v]) child[v] = new StringTrie();
            node->child[v] = child[v]->set(s, val, pos + 1);
        }
        return node;
    }

    int get(string &s, int pos = 0) {
        if (pos >= s.size()) return dat;
        int v = s[pos] - 'a';
        if (!child[v]) return -1;
        return child[v]->get(s, pos + 1);
    }
};

int main() {
    return 0;
}

// Phan-Viet Lam - lamphanviet@gmail.com - http://blog.lamphanviet.com