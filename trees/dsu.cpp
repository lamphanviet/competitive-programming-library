#include <bits/stdc++.h>
using namespace std;

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
#define N 1000111

struct Dsu {
    vector<int> lab, cnt;

    Dsu(int n) {
        lab.assign(n + 1, -1);
        cnt.assign(n + 1, 1);
    }

    int getRoot(int u) {
        return lab[u] < 0 ? u : lab[u] = getRoot(lab[u]);
    }

    int unionSet(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (cnt[u] < cnt[v]) swap(u, v);
        cnt[u] += cnt[v];
        return lab[v] = u;
    }
};

int main() {
    Dsu s(100);
    return 0;
}

// lamphanviet@gmail.com
