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
        return (x == o.x) ? y < o.y : x < o.x;
    }

    bool operator==(const pt& o) const {
        return (x == o.x && y == o.y);
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

// counter clockwise
bool ccw(pt a, pt b, pt c) {
    return cross(b - a, c - a) > 0;
}


/*
 * convex hull
 */

vector<pt> half_hull(vector<pt> pts) {
  vector<pt> res;
  for (int i = 0; i < pts.size(); i++) {
    // ccw means we have a left turn; we don't want that
    while (res.size() >= 2 &&
           ccw(pts[i], res[res.size()-1], res[res.size()-2])) {
      res.pop_back();
    }
    res.push_back(pts[i]);
  }
  return res;
}

vector<pt> convex_hull(vector<pt> pts) {
  sort(pts.begin(), pts.end());
  vector<pt> top = half_hull(pts);

  reverse(pts.begin(), pts.end());
  vector<pt> bottom = half_hull(pts);
  
  top.pop_back();
  bottom.pop_back();
  vector<pt> res(top.begin(), top.end());
  res.insert(res.end(), bottom.begin(), bottom.end());
  return res;
}


int main() {
    int n, m;
    ll x, y;
    vector<pt> pts, out, hull;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        pts.emplace_back(x, y);
        out.emplace_back(x, y);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        pts.emplace_back(x, y);
    }

    hull = convex_hull(pts);
    sort(hull.begin(), hull.end());
    sort(out.begin(), out.end());



    cout << ((hull == out) ? "YES" : "NO"); 




}