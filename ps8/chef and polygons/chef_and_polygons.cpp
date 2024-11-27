#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(var) cerr<< #var << " = " << var << endl
#define rep(i, n) for (int i = 0; i < n; i++)
#define debugArr(n, arr) rep(i, n) cerr << arr[i] << ' '; cerr << endl
const double EPS = 1e-8;
const int N = 105;
const int M = 3005;
const int LEFT = -1;
const int RIGHT = 1;

int cntin[N][N];
int cntout[N][N];

struct pt {
    ll x, y;
    pt() : x(0), y(0) {}
    pt(ll x_v, ll y_v) : x(x_v), y(y_v) {}

    bool operator<(const pt& o) const {
        return (x == o.x) ? y <= o.y : x <= o.x;
    }
};

vector<pt> rpts;
vector<pt> bpts;

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
bool ccw(pt a, pt b, pt c) {
    return cross(b - a, c - a) > 0;
}

bool queryPoint(pt b, int k, vector<int> poly) {
    pt pv = rpts[poly[0]], nx;
    for (int i = 1; i < k; i++) {
        nx = rpts[poly[i]];
        if (!ccw(pv, b, nx)) return false;
        pv = nx;
    }
    nx = rpts[poly[0]];
    if (!ccw(pv, b, nx)) return false;
    return true;
}

int main() {
    int n, m, q, x, y;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        rpts.push_back(pt(x, y));
    } 

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        bpts.push_back(pt(x, y));
    } 

    cin >> q;
    int qn, p;
    for (int i = 0; i < q; i++) {
        cin >> qn;
        vector<int> ids;
        int cnt = 0;
        for (int j = 0; j < qn; j++) {
            cin >> p;
            ids.push_back(p-1);
        }


        for (pt pts : bpts) {
            if (queryPoint(pts, qn, ids)) cnt++;
        }
        cout << cnt << endl;
    }


}
