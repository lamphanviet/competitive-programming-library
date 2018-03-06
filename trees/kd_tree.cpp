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
#define N 200002

// problem: https://www.hackerrank.com/challenges/maximizing-mission-points/problem

ll NIL = -(1LL < 60);
template<typename T>
struct KDTree {
	bool direction;
	int x0, xn, y0, yn;
	T data;

	KDTree *left, *right;

	KDTree() {
		left = right = NULL;
		data = NIL;
	}

	KDTree(KDTree *parent, bool side) {
		direction = !parent->direction;
		x0 = parent->x0;
		xn = parent->xn;
		y0 = parent->y0;
		yn = parent->yn;
		left = right = NULL;
		data = NIL;
		if (direction) {
			int mid = (x0 + xn) >> 1;
			if (side) xn = mid;
			else x0 = mid + 1;
		} else {
			int mid = (y0 + yn) >> 1;
			if (side) yn = mid;
			else y0 = mid + 1;
		}
	}

	inline bool isLeaf() {
		return x0 == xn && y0 == yn;
	}

	inline bool contains(int x, int y) {
		return (x0 <= x && x <= xn && y0 <= y && y <= yn);
	}

	inline bool contains(int x1, int x2, int y1, int y2) {
		return contains(x1, y1) && contains(x2, y2);
	}

	inline bool overlap(int x1, int x2, int y1, int y2) {
		return max(x0, x1) <= min(xn, x2) && max(y0, y1) <= min(yn, y2);
	}

	inline bool inside(int x1, int x2, int y1, int y2) {
		return x1 <= x0 && xn <= x2 && y1 <= y0 && yn <= y2;
	}

	// update and maybe insert new node with value, only suitable for dynamic tree
	T insert(int x, int y, T val) {
		if (!contains(x, y)) return data;
		if (isLeaf()) {
			return data = max(data, val);
		}
		if (left == NULL) left = new KDTree(this, true);
		if (right == NULL) right = new KDTree(this, false);
		T ld = left->insert(x, y, val);
		T rd = right->insert(x, y, val);
		return data = max(ld, rd);
	}

	// update the existing nodes, no new node creation, the tree has to be built up-front
	T update(int x, int y, T val) {
		if (!contains(x, y)) return data;
		if (isLeaf()) {
			return data = max(data, val);
		}
		data = NIL;
		if (left != NULL) {
			data = max(data, left->update(x, y, val));
		}
		if (right != NULL) {
			data = max(data, right->update(x, y, val));
		}
		return data;
	}

	T get(int x1, int x2, int y1, int y2) {
		if (!overlap(x1, x2, y1, y2)) return NIL;
		if (inside(x1, x2, y1, y2)) {
			return data;
		}
		T res = NIL;
		if (left != NULL) res = max(res, left->get(x1, x2, y1, y2));
		if (right != NULL) res = max(res, right->get(x1, x2, y1, y2));
		return res;
	}

	void get(int x1, int x2, int y1, int y2, T &res) {
		if (data <= res) return;
		if (!overlap(x1, x2, y1, y2)) return;
		if (inside(x1, x2, y1, y2)) {
			res = max(res, data);
			return;
		}
		if (left != NULL) left->get(x1, x2, y1, y2, res);
		if (right != NULL) right->get(x1, x2, y1, y2, res);
	}
};

struct City {
	int h, lat, lng, points;

	bool operator < (const City &c) const {
		if (h == c.h) {
			if (lat == c.lat) return lng < c.lng;
			return lat < c.lat;
		}
		return h < c.h;
	}
};
int n, dlat, dlng;
City a[N];
KDTree<ll> *root;

bool cmp1(const City &a, const City &b) {
	return a.lat < b.lat;
}

bool cmp2(const City &a, const City &b) {
	return a.lng < b.lng;
}

KDTree<ll> *buildTree(int lo, int hi) {
	KDTree<ll> *node = new KDTree<ll>();
	node->direction = true;
	node->x0 = node->xn = a[lo].lat;
	node->y0 = node->yn = a[lo].lng;
	if (lo == hi) {
		return node;
	}

	fr(i, lo, hi) {
		node->x0 = min(node->x0, a[i].lat);
		node->xn = max(node->xn, a[i].lat);
		node->y0 = min(node->y0, a[i].lng);
		node->yn = max(node->yn, a[i].lng);
	}

	// partitioning based on the range
	int dx = node->xn - node->x0;
	int dy = node->yn - node->y0;
	node->direction = dx > dy;

	sort(a + lo, a + hi + 1, node->direction ? cmp1 : cmp2);
	int mid = (lo + hi) >> 1;
	node->left = buildTree(lo, mid);
	node->right = buildTree(mid + 1, hi);
	return node;
}

ll getMax(int x1, int x2, int y1, int y2) {
	ll res = 0;
	x1 = max(0, x1);
	x2 = min(N, x2);
	y1 = max(0, y1);
	y2 = min(N, y2);
	root->get(x1, x2, y1, y2, res);
	return res;
}

ll solve() {
	root = buildTree(0, n - 1);
	sort(a, a + n);
	ll res = NIL;
	rep(i, n) {
		ll fa = getMax(a[i].lat - dlat, a[i].lat + dlat, a[i].lng - dlng, a[i].lng + dlng);
		fa += a[i].points;
		if (fa > 0) root->update(a[i].lat, a[i].lng, fa);
		res = max(res, fa);
	}
	return res;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("inp.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	#endif
	ri(n); ri(dlat); ri(dlng);
	rep(i, n) {
		ri(a[i].lat);
		ri(a[i].lng);
		ri(a[i].h);
		ri(a[i].points);
	}
	cout << solve() << endl;
	return 0;
}
// lamphanviet@gmail.com