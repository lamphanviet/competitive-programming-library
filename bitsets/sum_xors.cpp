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

// problem: https://www.hackerrank.com/challenges/xor-se/problem

int q;
ll a, b;

ll sumXor(ll n) {
	ll res = 0;
	while ((n + 1) % 4 != 0) {
		res ^= n;
		n--;
	}
	return res;
}

ll sumXorXor(ll n) {
	ll m = ((n + 1) / 8) * 8;
	if (n + 1 == m) return 0;
	ll res = 0;
	for (ll i = m + 1; i <= n; i += 2) {
		res ^= i;
	}
	if ((n - m) % 2 == 0) {
		res ^= sumXor(n);
	}
	return res;
}

ll solve() {
	return sumXorXor(b) ^ sumXorXor(a - 1);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("inp.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	#endif
	ri(q);
	while (q--) {
		cin >> a >> b;
		cout << solve() << endl;
	}
	return 0;
}
// lamphanviet@gmail.com