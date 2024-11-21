#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(var) cerr<< #var << " = " << var << endl
#define rep(i, n) for (int i = 0; i < n; i++)
#define debugArr(n, arr) rep(i, n) cerr << arr[i] << ' '; cerr << endl
#define x first
#define y second
const double EPS = 1e-8;
struct pt {
    ll x, y;

    pt(ll x_v, ll y_v) : x(x_v), y(y_v) {}

    bool operator<(const pt& o) const {
        return (x == o.x) ? y <= o.y : x <= o.x;
    }
};

/*
 * cross product
 */

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

double cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}

// colinear
bool cl(pt a, pt b, pt c) {
    return cross(b - a, c - a) == 0;
}

int main() {
    ll n, x, y;
    vector<pair<pt, int>> pts;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        pts.push_back(make_pair(pt(x, y), i+1));
    }

    sort(pts.begin(), pts.end());

    for (int i = 0; i < n - 2; i++) {
        if (cl(pts[i].first, pts[i+1].first, pts[i+2].first)) continue;
        printf("%d %d %d\n", pts[i].second, pts[i+1].second, pts[i+2].second);
        return 0;
    }
}
