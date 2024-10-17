#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
const int MAXN = 2e5 + 10;
const ll INF = 1e18;
int N, M, K;
string s;
vector<pll> ord[MAXN];
ll dp[MAXN];


struct SegmentTree {

    vector<ll> t;

    SegmentTree(int n) {
        t.resize(4 * n);
    }

    void build(int i, int l, int r) {
        if (l == r) t[i] = INF;
        else {
            int m = (l + r) / 2;
            build(2 * i + 1, l, m);
            build(2 * i + 2, m + 1, r);
            t[i] = combine(t[2 * i + 1], t[2 * i + 2]);
        }
    }

    ll combine(ll l, ll r) {
        ll out;   
        out = min(l, r);
        return out;
    }


    void update(int i, int l, int r, int id, ll v) {
        if (l == r) {
            t[i] = v;
        } else {
            int m = (l + r) / 2;
            if (id <= m) {
                update(2 * i + 1, l, m, id, v);
            } else {
                update(2 * i + 2, m+1, r, id, v);
            }
            t[i] = combine(t[2 * i + 1], t[2 * i + 2]);
        }
    }

    ll queryMin(int i, ll l, ll r, ll L, ll R) {
        if (L > r || R < l) return INF;
        if (L <= l && R >= r) return t[i];
        int m = (l + r) / 2;
        return min(queryMin(2 * i + 1, l, m, L, R), queryMin(2 * i + 2, m + 1, r, L, R));
    }

};

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cin >> N >> K;
    cin >> s;
    
    for (int i = 1; i <= N; i++) {
        ord[i].push_back(make_pair(i, i));
        if (s[i-1] == '1') {
            ord[min(N, i+K)].push_back(make_pair(max(1, i-K), i));
        }
    }

    SegmentTree tree(N+1);
    tree.build(0, 0, N);

    for (int i = 0; i <= N; i++) {
        dp[i] = (i == 0) ? 0 : INF;
        for (auto o : ord[i]) {
            ll prevCost = (o.first == 0) ? 0 : tree.queryMin(0, 0, N, o.first - 1, i - 1);
            dp[i] = min(dp[i], prevCost + o.second);
        }
        tree.update(0, 0, N, i, dp[i]);
    }

    cout << dp[N] << endl;;
   
}