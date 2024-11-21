#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(var) cerr<< #var << " = " << var << endl
#define rep(i, n) for (int i = 0; i < n; i++)
#define debugArr(n, arr) rep(i, n) cerr << arr[i] << ' '; cerr << endl
#define x first
#define y second
const double EPS = 1e-8;
const ll INF = 1e18;

struct pt {
    ll x, y;

    pt(ll x_v, ll y_v) : x(x_v), y(y_v) {}

    bool operator<(const pt& o) const {
        return (x == o.x) ? y <= o.y : x <= o.x;
    }
};

vector<pt> pts;
int n;


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

bool work(int a, int b) {
    vector<int> unvis;
    pt pta = pts[a], ptb = pts[b];

    for (int i = 0; i < n; i++) {
        if (!cl(pta, ptb, pts[i])) unvis.push_back(i);
    }

    if (unvis.size() < 3) return true;
     
    auto it = unvis.begin();
    pta = pts[*it]; it++; ptb = pts[*it]; it++;
    for (it; it != unvis.end(); it++) {
        if (!cl(pta, ptb, pts[*it])) return false;
    }

    return true;

}

int main() {
    ll x, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        pts.push_back(pt(x, y));
    }

    if (n <= 4 || work(0,1) || work(0,2) || work(1,2)) cout << "YES\n";
    else cout << "NO\n";

}
