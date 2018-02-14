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
#define N 1000001


template<typename T>
struct BIndexTree {
    int n;
    vector<T> value;
    
    BIndexTree(int n) {
        this->n = n;
        value.assign(n, 0);
    }

    T get(int i) {
        T res = 0;
        while (i > 0) {
            res += value[i];
            i -= i & -i;
        }
        return res;
    }

    T get(int lo, int hi) {
        return get(hi) - get(lo - 1);
    }

    void add(int i, int val) {
        while (i < n) {
            value[i] += val;
            i += i & -i;
        }
    }
};

int main() {
    BIndexTree<int> btree(100);
    return 0;
}