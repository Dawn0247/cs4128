#include <bits/stdc++.h>
#define ll long long 
using namespace std;

const int MAXN = 10e5+5;
int N, M;
vector<ll> arr(MAXN);

struct SegmentTree {
    struct Node {
        ll sum, maxVal, minVal;
        bool inc, dec;
    };

    vector<Node> t;

    SegmentTree(int n) {
        t.resize(4 * n);
    }

    void build(int i, int l, int r) {
        if (l == r) t[i] = {arr[l], arr[l], arr[l], true, true};
        else {
            int m = (l + r) / 2;
            build(2 * i + 1, l, m);
            build(2 * i + 2, m + 1, r);
            t[i] = combine(t[2 * i + 1], t[2 * i + 2]);
        }
    }

    Node combine(Node l, Node r) {
        Node out;   
        out.sum = l.sum + r.sum;
        out.maxVal = max(l.maxVal, r.maxVal);
        out.minVal = min(l.minVal, r.minVal);
        out.inc = l.inc && r.inc && l.maxVal <= r.minVal;
        out.dec = l.dec && r.dec && l.minVal >= r.maxVal;
        return out;
    }


    void update(int i, int l, int r, int id, ll v) {
        if (l == r) {
            arr[l] = v;
            t[i] = {v, v, v, true, true};
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

    // L and R: left and right bound
    int querySum(int i, ll l, ll r, ll L, ll R) {
        if (L > r || R < l) return 0;
        if (L <= l && R >= r) return t[i].sum;
        int m = (l + r) / 2;
        return querySum(2 * i + 1, l, m, L, R) + querySum(2 * i + 2, m + 1, r, L, R);
    }

    int queryMax(int i, ll l, ll r, ll L, ll R) {
        if (L > r || R < l) return -1;
        if (L <= l && R >= r) return t[i].maxVal;
        int m = (l + r) / 2;
        return max(queryMax(2 * i + 1, l, m, L, R), queryMax(2 * i + 2, m + 1, r, L, R));
    }

    int queryInc(int i, ll l, ll r, ll L, ll R, ll &lmax) {
        if (L > r || R < l) return true;
        if (L <= l && R >= r) {
            if (t[i].inc && lmax <= t[i].minVal) {
                lmax = t[i].maxVal;
                return true;
            } else {
                return false;
            }
        }
        int m = (l + r) / 2;
        return queryInc(2 * i + 1, l, m, L, R, lmax) && queryInc(2 * i + 2, m + 1, r, L, R, lmax);
    }

    int queryDec(int i, ll l, ll r, ll L, ll R, ll &lmin) {
        if (L > r || R < l) return true;
        if (L <= l && R >= r) {
            if (t[i].dec && lmin >= t[i].maxVal) {
                lmin = t[i].maxVal;
                return true;
            } else {
                return false;
            }
        }
        int m = (l + r) / 2;
        return queryDec(2 * i + 1, l, m, L, R, lmin) && queryDec(2 * i + 2, m + 1, r, L, R, lmin);
    }



};



int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    SegmentTree tree(N);
    tree.build(0, 0, N-1);

    for (int j; j < M; j++) {
        char cmd;
        ll x, y;
        cin >> cmd >> x >> y;
        x--, y--;

        switch (cmd) {
            case 'U':
                tree.update(0, 0, N-1, x, y + 1);
                break;
            case 'M':
                cout << tree.queryMax(0, 0, N-1, x, y) << '\n';
                break;
            case 'S':
                cout << tree.querySum(0, 0, N-1, x, y) << '\n';
                break;
            case 'I': {
                ll lmax = -1;
                cout << tree.queryInc(0, 0, N-1, x, y, lmax) << '\n';
                break;
            }   
            case 'D': {
                 ll lmin = 10e9+5;
                cout << tree.queryDec(0, 0, N-1, x, y, lmin) << '\n';
                break; 
            }
            default:
                break;
                
        }


    }   
} 