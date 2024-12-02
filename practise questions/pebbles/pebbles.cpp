#include <bits/stdc++.h>
#define ll long long
#define flag(f) cerr << "FLAG: " << f << endl
#define debug(var) cerr << #var << ": " << var << endl
using namespace std;
const int MAXN = 15;
int arr[MAXN][MAXN];
int dp[MAXN][1 << MAXN];
int n, m;

bool checkMask(int upperMask, int lowerMask) {
    for (int shift = 1; shift < n; shift++) {
        // check horizontal adjacency
        if ((lowerMask & (1 << shift)) && (lowerMask & (1 << (shift - 1)))) {
            // flag(1);
            return false;
        }

        // check backwards diagonal adjacency
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

    for (int shift = 0; shift < (n-1); shift++) {
        // check forwards diagonal adjacency
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


int getRowSum(int i, int mask) {
    int out = 0;
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) out += arr[i][j];
    }
    return out;
}

int work() {
    // base case
    for (int mask = 0; mask < (1 << n); mask++) {
        if (checkMask(0, mask)) {
            // debug(mask);
            dp[0][mask] = getRowSum(0, mask);

        }
    }
    // next row
    for (int j = 1; j < n; j++) {
        // old mask
        for (int mask = 0; mask < (1 << n); mask++) {
            if (checkMask(0, mask)) {
                // debug(mask);
                dp[0][mask] = getRowSum(0, mask);

            }
        }
    }

    for (int i = 0; i < (1 << n); i++) {
        cout << dp[0][i] << ' ';
    } cout << endl;

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m;
    while (m--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << ' ';
            } cout << endl;
        }
        cout << n << endl;
        work();
        break;

    }

}
