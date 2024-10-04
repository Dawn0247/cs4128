#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define ll long long 
const int MAXN = 18;
int N, M, K;
ll arr[MAXN];
ll dp[1 << MAXN][MAXN];
ll bonuses[MAXN][MAXN];

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    for(int i = 0; i < K; i++) {
        int d1, d2, bonus;
        cin >> d1 >> d2 >> bonus;
        bonuses[d1-1][d2-1] = bonus;
    } 
        

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         cout << bonuses[i][j] << ' ';
    //     } cout << '\n';
    // }
        

    // for (int i = 0; i < N; i++) {
    //     cout << arr[i] << ' ';
    // } cout << endl;

    for (int i = 0; i < N; i++) {
        dp[1 << i][i] = arr[i];
    }

    // i: current dish
    // j: next dish
    for (int mask = 0; mask < (1 << N); mask++) {
        for (int i = 0; i < N; i++) {
            // if current dish isnt eaten
            if ( !(mask & (1 << i)) ) continue;

            for (int j = 0; j < N; j++) {
                // if the next dish has already been eaten
                if (mask & (1 << j)) continue;

                // update mask to include j
                int newMask = mask | (1 << j);

                ll val = dp[mask][i] + arr[j] + bonuses[i][j];
                if (val > dp[newMask][j]) { 
                    dp[newMask][j] = val;
                }
            }
        }
    }
    
    ll mxm = LLONG_MIN;
    for (int mask = 0; mask < (1 << N); mask++) {
        if (__builtin_popcount(mask) == M) {
            for (int i = 0; i < N; i++) {
                if (dp[mask][i] > mxm) {
                    mxm = dp[mask][i];
                }
            }
        }
    }   

    cout << mxm << endl;
}
