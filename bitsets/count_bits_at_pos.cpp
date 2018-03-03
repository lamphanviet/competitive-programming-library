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

#define BIT(n) (1<<(n))
#define AND(a,b) ((a) & (b))
#define OR(a,b) ((a) | (b))
#define XOR(a,b) ((a) ^ (b))
#define sqr(x) ((x) * (x))

#define ri(a) scanf("%d", &a)
#define rs(a) scanf("%s", &a)

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define PI  3.1415926535897932385
#define EPS 1e-7
#define MOD 1000000007
#define INF 1500111222
#define N 100111

// problem: https://www.hackerrank.com/challenges/and-product/problem

int q;
ll a, b;

ll countBits(ll n, int pos) {
	if (n < (1LL << pos)) return 0;
	ll res = 0;
	for (int i = 60; i >= pos; i--) {
		if (n & (1LL << i)) {
			if (i == pos) {
				res += n - (1LL << i) + 1;
			} else {
				res += (1LL << i) / 2;
			}
			n ^= (1LL << i);
		}
	}
	return res;
}

ll solve() {
	ll res = 0;
	repr(i, 60) {
		ll bits = countBits(b, i) - countBits(a - 1, i);
		if (bits == b - a + 1) {
			res |= (1LL << i);
		}
	}
	return res;
}

int main() {
	ri(q);
	while (q--) {
		cin >> a >> b;
		cout << solve() << endl;
	}
	return 0;
}
// lamphanviet@gmail.com