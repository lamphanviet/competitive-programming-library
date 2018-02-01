#include <bits/stdc++.h>
using namespace std;

/**
* Lawler algorithm - using to find maximum matching in general graphs
*/
struct Lawler {
    static const int NIL = -1;

    int n, start, finish;
    vector<vector<int> > adj;
    vector<int> match, b, t;
    vector<bool> inQueue, mark, inPath;
    queue<int> que;

    // construct with the size of the graph
    // all nodes are numberred from 0 to n - 1
    Lawler(int n) {
        this->n = n;
        adj = vector<vector<int> >(n);
        match = b = t = vector<int>(n);
        inQueue = mark = inPath = vector<bool>(n);
    }

    // add a new undirect edge between node u and node v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // call this to find maximum matching after building the graph
    // this will return list of pairs (matchings)
    vector<pair<int, int> > maximumMatching() {
        match = vector<int>(n, NIL);
        for (int u = 0; u < n; u++) {
            if (match[u] == NIL) {
                start = u;
                finish = findAugmentingPath();
                if (finish != NIL) enlarge();
            }
        }
        vector<pair<int, int> > pairs;
        for (int u = 0; u < n; u++)
        	if (match[u] > u)
            	pairs.push_back(make_pair(u, match[u]));
        return pairs;
    }

    inline void pushQueue(int u) { que.push(u); inQueue[u] = true; }

    inline int popQueue() { int u = que.front(); que.pop(); return u; }


    int findCommonAncestor(int p, int q) {
        inPath = vector<bool>(n, false);
        while (true) {
            p = b[p];
            inPath[p] = true;
            if (p == start) break;
            p = t[match[p]];
        }
        while (true) {
            q = b[q];
            if (inPath[q]) return q;
            q = t[match[q]];
        }
        return NIL;
    }

    void resetTrace(int x, int newBase) {
        int v = x;
        while (b[v] != newBase) {
            int u = match[v];
            mark[b[v]] = true;
            mark[b[u]] = true;
            v = t[u];
            if (b[v] != newBase) t[v] = u;
        }
    }

    void blossomShrink(int p, int q) {
        mark = vector<bool>(n, false);
        int newBase = findCommonAncestor(p, q);
        resetTrace(p, newBase); resetTrace(q, newBase);
        if (b[p] != newBase) t[p] = q;
        if (b[q] != newBase) t[q] = p;
        for (int i = 0; i < n; i++) {
            if (mark[b[i]]) b[i] = newBase;
            if (!inQueue[i] && b[i] == newBase) {
                pushQueue(i);
            }
        }
    }


    int findAugmentingPath() {
        que = queue<int>();
        inQueue = vector<bool>(n, false);
        pushQueue(start);

        for (int i = 0; i < n; i++)
        	t[i] = NIL, b[i] = i;
        finish = NIL;

        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (match[u] != v && b[u] != b[v]) {
                    if ((v == start) || (match[v] != NIL) && (t[match[v]] != NIL))
                        blossomShrink(u, v);
                    else {
                        if (t[v] == NIL) {
                            if (match[v] == NIL) {
                                t[v] = u;
                                return v;
                            }
                            else {
                                t[v] = u;
                                pushQueue(match[v]);
                            }
                        }
                    }
                }
            }
        }
        return NIL;
    }

    void enlarge() {
        int u, next;
        do {
            u = t[finish];
            next = match[u];
            match[u] = finish;
            match[finish] = u;
            finish = next;
        } while (finish != NIL);
    }
};

int main() { return 0; }

// Phan-Viet Lam - lamphanviet@gmail.com - http://blog.lamphanviet.com