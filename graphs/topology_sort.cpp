#include <bits/stdc++.h>

using namespace std;

#define fr(i,a,b) for (int i = (a), _b = (b); i <= _b; i++)
#define rep(i,n) for (int i = 0, _n = (n); i < _n; i++)

#define all(ar) ar.begin(), ar.end()
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

typedef vector<int> vi;

#define N 300111
#define M 26

int n;
vi adj[N], order;
bool pending[N], mark[N], cycle;

void dfs(int u) {
    if (cycle) return;
    mark[u] = true;
    pending[u] = true;
    rep(i, adj[u].size()) {
        int v = adj[u][i];
        if (mark[v] && pending[v]) {
            cycle = true;
            return;
        } else if (!mark[v]) dfs(v);
    }
    pending[u] = false;
    order.pb(u);
}

// sort and put the nodes in order
// cycle is true if there is cycle in the graph
void topology_sort() {
    cycle = false;
    fr(i, 1, n) if (!mark[i]) {
        dfs(i);
    }
    reverse(all(order));
}

int main() {
    return 0;
}