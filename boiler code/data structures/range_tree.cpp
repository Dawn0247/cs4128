#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll,ll>
#define repRange(x,y,i) for (int i = x; i < y; i++)
#define printArr(n, arr) repRange(0, n, i) { cerr << arr[i] << ' '; } cerr << endl
#define print2DArr(n, m, arr) repRange(0, n, j) { printArr(m, arr[j]); }
#define printPairArr(n, arr) repRange(0, n, i) { cerr << arr[i].first << ' ' << arr[i].second << '\n'; };
#define debug(var) cerr << #var << ": " <<  var << endl
#define flag(i) cerr << "Flag: " << i

using namespace std;
const int MAXN = 1e5; // Maximum number of elements

struct RangeTree {
    int arr[MAXN];
    int rangeMin[4 * MAXN];
    int rangeMax[4 * MAXN];
    int rangeSum[4 * MAXN];

    // Build Range Tree for min, max, and sum
    void build(int idx, int l, int r) {
        if (l == r) {
            rangeMin[idx] = rangeMax[idx] = rangeSum[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx + 1, l, mid);
        build(2 * idx + 2, mid + 1, r);
        rangeMin[idx] = min(rangeMin[2 * idx + 1], rangeMin[2 * idx + 2]);
        rangeMax[idx] = max(rangeMax[2 * idx + 1], rangeMax[2 * idx + 2]);
        rangeSum[idx] = rangeSum[2 * idx + 1] + rangeSum[2 * idx + 2];
    }

    // Update the value at position pos to new_val
    void update(int idx, int l, int r, int pos, int new_val) {
        if (l == r) {
            rangeMin[idx] = rangeMax[idx] = rangeSum[idx] = arr[l] = new_val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(2 * idx + 1, l, mid, pos, new_val);
        } else {
            update(2 * idx + 2, mid + 1, r, pos, new_val);
        }
        rangeMin[idx] = min(rangeMin[2 * idx + 1], rangeMin[2 * idx + 2]);
        rangeMax[idx] = max(rangeMax[2 * idx + 1], rangeMax[2 * idx + 2]);
        rangeSum[idx] = rangeSum[2 * idx + 1] + rangeSum[2 * idx + 2];
    }

    // Query for minimum value in range [ql, qr]
    int queryMin(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INT_MAX;
        if (ql <= l && r <= qr) return rangeMin[idx];
        int mid = (l + r) / 2;
        return min(queryMin(2 * idx + 1, l, mid, ql, qr), queryMin(2 * idx + 2, mid + 1, r, ql, qr));
    }

    // Query for maximum value in range [ql, qr]
    int queryMax(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INT_MIN;
        if (ql <= l && r <= qr) return rangeMax[idx];
        int mid = (l + r) / 2;
        return max(queryMax(2 * idx + 1, l, mid, ql, qr), queryMax(2 * idx + 2, mid + 1, r, ql, qr));
    }

    // Query for sum in range [ql, qr]
    int querySum(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return rangeSum[idx];
        int mid = (l + r) / 2;
        return querySum(2 * idx + 1, l, mid, ql, qr) + querySum(2 * idx + 2, mid + 1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    RangeTree rt;
    int nums[] = {0, 7, 3, 5, 6, 1, 4, 9, 2, 8};
    for (int i = 0; i < 10; i++) {
        rt.arr[i] = nums[i];
    }
    rt.build(0, 0, 9);

    debug(rt.queryMax(0, 0, 9, 4, 8));
    debug(rt.queryMin(0, 0, 9, 1, 4));
    debug(rt.querySum(0, 0, 9, 3, 9));
    debug(rt.querySum(0, 0, 9, 0, 3));
    rt.update(0, 0, 9, 1, 1);
    debug(rt.querySum(0, 0, 9, 0, 3));


    return 0;
}
