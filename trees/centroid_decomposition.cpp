#include <bits/stdc++.h>
using namespace std;

// test problem: http://codeforces.com/contest/914/problem/E

#define fr(i,a,b) for (int i = (a), _b = (b); i <= _b; i++)
#define frr(i,a,b) for (int i = (a), _b = (b); i >= _b; i--)
#define rep(i,n) for (int i = 0, _n = (n); i < _n; i++)
#define repr(i,n) for (int i = (n) - 1; i >= 0; i--)
#define foreach(it, ar) for ( typeof(ar.begin()) it = ar.begin(); it != ar.end(); it++ )
#define fill(ar, val) memset(ar, val, sizeof(ar))

#define ull unsigned long long
#define ll long long
#define all(ar) ar.begin(), ar.end()
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define ri(a) scanf("%d", &a)
#define rs(a) scanf("%s", &a)

#define PI  3.1415926535897932385
#define EPS 1e-7
#define MOD 1000000007
#define INF 1500111222
#define N 200111

int n, size[N];
char s[N];
int lab[N];
vi adj[N];
bool del[N];
int cnt[1 << 20];
ll res[N], res2[N], f[N];

// finding size of all subtrees starting from node u
void dfs(int u, int p) {
    size[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !del[v]) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

// return centroid of the subtree containg node u
int findCentroid(int u) {
    int p = -1; dfs(u, -1);
    int cap = size[u] >> 1;
    while (true) {
        bool found = false;
        for (int v : adj[u]) {
            if (v != p && !del[v] && size[v] > cap) {
                found = true;
                p = u; u = v;
                break; // going deeper if size[v] is large enough
            }
        }
        if (!found) return u;
    }
}

void contribute(int u, int p, int curLab, int val) {
    cnt[curLab] += val;
    for (int v : adj[u]) {
        if (v != p && !del[v]) {
            contribute(v, u, curLab ^ lab[v], val);
        }
    }
}

void update(int root, int u, int p, int curLab) {
    int labToRoot = curLab ^ lab[root];
    // to other branch, always double updates at root node
    f[u] = cnt[labToRoot];
    res2[root] += cnt[labToRoot];
    rep(i, 20) {
        int neededLab = (1 << i) ^ labToRoot;
        f[u] += cnt[neededLab];
        res2[root] += cnt[neededLab];
    }
    // to root, no double update
    if (!labToRoot || __builtin_popcount(labToRoot) <= 1) {
        f[u]++;
        res[root]++;
    }
    for (int v : adj[u]) {
        if (v != p && !del[v]) {
            update(root, v, u, curLab ^ lab[v]);
            f[u] += f[v];
        }
    }
    res[u] += f[u];
}

void cal(int u) {
    res[u]++;
    for (int v : adj[u]) {
        if (!del[v]) contribute(v, u, lab[v], 1);
    }
    for (int v : adj[u]) {
        if (!del[v]) {
            contribute(v, u, lab[v], -1);
            update(u, v, u, lab[v]);
            contribute(v, u, lab[v], 1);
        }
    }
    for (int v : adj[u]) {
        if (!del[v]) contribute(v, u, lab[v], -1);
    }
}

void divide(int u) {
    u = findCentroid(u);
    del[u] = true; cal(u);
    for (int v : adj[u]) {
        if (!del[v]) {
            divide(v);
        }
    }
}

void solve() {
    rep(i, n) lab[i] = 1 << (int)(s[i] - 'a');
    divide(0);
    rep(i, n) printf("%lld ", res[i] + res2[i] / 2);
    puts("");
}

int main() {
    //ios::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen("inp.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    #endif
    int u, v;
    ri(n);
    rep(i, n -1) {
        ri(u); ri(v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    rs(s);
    solve();
    return 0;
}

// lamphanviet@gmail.com

