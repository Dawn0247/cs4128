#include <bits/stdc++.h>
#define ll long long
#define flag(f) cerr << "FLAG: " << f << endl
#define debug(var) cerr << #var << ": " << var << endl
using namespace std;
const int MAXN = 15;
int arr[MAXN][MAXN];
int dp[MAXN][1 << MAXN];
map<int, vector<int>> masks;
vector<int> validMasks;
int n, m;

bool checkMask(int upperMask, int lowerMask) {
    for (int shift = 1; shift < MAXN; shift++) {
        // check horizontal adjacency
        if ((lowerMask & (1 << shift)) && (lowerMask & (1 << (shift - 1)))) {
            // flag(1);
            return false;
        }

        // check forward diagonal adjacency
        if ((lowerMask & (1 << shift)) && (upperMask & (1 << (shift - 1)))) {
            // flag(2);
            return false;
        }

        // check vertical adjacency (misses first bit)
        if ((lowerMask & (1 << shift)) && (upperMask & (1 << shift))) {
            // flag(3);
            return false;
        }
    }

    for (int shift = 0; shift < (MAXN-1); shift++) {
        // check back diagonal adjacency
        if ((lowerMask & (1 << shift)) && (upperMask & (1 << (shift + 1)))) {
            // flag(4);
            return false;
        }
    }

    // checks vertical adjacency (first bit)
    if ((lowerMask & 1) && (upperMask & 1)) {
        // flag(5);
        return false;
    }
    
    return true;
}

void preProc() {
    masks.clear();
    validMasks.clear();
    for (int mask = 0; mask < (1 << MAXN); mask++) {
        if (checkMask(0, mask)) {
            masks[mask] = vector<int>();
            validMasks.push_back(mask);
        }
    }

    for (int k : validMasks) {
        for (int mask : validMasks) {
            if (checkMask(k, mask)) {
                masks[k].push_back(mask);
            }
        }
    }
}


int getRowSum(int i, int mask) {
    int out = 0;
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) out += arr[i][j];
    }
    return out;
}

int work() {
    for (int mask : validMasks) {
        dp[0][mask] = getRowSum(0, mask);
    }

    // next row
    for (int j = 1; j < n; j++) {
        // new mask
        for (int newMask : validMasks) {
            int rowSum = getRowSum(j, newMask);
            // next mask
            vector<int> oldMasks = masks[newMask];
            for (int oldMask : oldMasks) {
                dp[j][newMask] = max(dp[j][newMask], dp[j-1][oldMask] + rowSum);
            }
        }
    }
    int mxm = 0;
    for (int m = 0; m < (1 << n); m++) {
        mxm = max(mxm, dp[n-1][m]);
    } 
    cout << mxm << endl;

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    preProc();

    cin >> m;
    while (m--) {
        cin >> n;
        fill_n(&dp[0][0], MAXN * (1 << MAXN), 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }

        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         cout << arr[i][j] << ' ';
        //     } cout << endl;
        // }
        // cout << n << endl;
        // for (auto [k, v] : masks) {
        //     cout << k << ": ";
        //     for (int i : v) {  
        //         cout << i << ' ';
        //     }
        //     cout << endl;
        // }
        work();
        

    }

}
