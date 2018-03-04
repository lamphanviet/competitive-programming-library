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

// problem: https://www.hackerrank.com/challenges/aorb/problem

int k;
string a, b, c;

int hexaToInt(char c) {
	if ('0' <= c && c <= '9') return c - '0';
	return c - 'A' + 10;
}

char intToHexa(int n) {
	if (0 <= n && n <= 9) return n + '0';
	return n - 10 + 'A';
}

void refine(int cnt) {
	repr(i, c.size()) {
		if (cnt >= k) break;
		int ic = hexaToInt(c[i]);
		int ia = hexaToInt(a[i]);
		int ib = hexaToInt(b[i]);
		repr(j, 4) {
			if (cnt >= k) break;
			int bit = 1 << j;
			if (ic & bit) {
				if ((ia & bit) && (ib & bit)) {
					ia ^= bit;
					cnt++;
				} else if (ia & bit) {
					if (cnt + 2 <= k) {
						ia ^= bit;
						ib ^= bit;
						cnt += 2;
					}
				}
			}
		}
		a[i] = intToHexa(ia);
		b[i] = intToHexa(ib);
	}
	while (a.size() > 1 && a.back() == '0') {
		a.pop_back();
	}
	while (b.size() > 1 && b.back() == '0') {
		b.pop_back();
	}
}

bool solve() {
	int cnt = 0;
	reverse(all(a));
	reverse(all(b));
	reverse(all(c));
	while (a.size() < c.size()) a.pb('0');
	while (b.size() < c.size()) b.pb('0');
	rep(i, c.size()) {
		int ic = hexaToInt(c[i]);
		int ia = hexaToInt(a[i]);
		int ib = hexaToInt(b[i]);
		rep(j, 4) {
			int bit = 1 << j;
			if (ic & bit) {
				if (!(ia & bit) && !(ib & bit)) {
					ib |= bit;
					cnt++;
				}
			} else {
				if (ia & bit) {
					ia ^= bit;
					cnt++;
				}
				if (ib & bit) {
					ib ^= bit;
					cnt++;
				}
			}
		}
		a[i] = intToHexa(ia);
		b[i] = intToHexa(ib);
        if (cnt > k) return false;
	}
	while (a.size() > c.size()) {
		cnt += __builtin_popcount(hexaToInt(a.back()));
		a.pop_back();
	}
	while (b.size() > c.size()) {
		cnt += __builtin_popcount(hexaToInt(b.back()));
		b.pop_back();
	}
	if (cnt <= k) {
		refine(cnt);
		reverse(all(a));
		reverse(all(b));
		cout << a << endl << b << endl;
		return true;
	}
	return false;
}

int main() {
	int q;
	ri(q);
	while (q--) {
		ri(k);
		cin >> a >> b >> c;
		if (!solve()) {
			puts("-1");
		}
	}
	return 0;
}
// lamphanviet@gmail.com