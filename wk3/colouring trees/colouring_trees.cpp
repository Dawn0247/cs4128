
#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define ll long long 
const long long INF = 1e18;
const int MAXN = 101;
int N, M, K;
ll arr[MAXN];
ll p[MAXN][MAXN];
ll dp[MAXN][MAXN][MAXN];

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    } 

    // paint[i][j] = cost paint tree i into color j
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> p[i][j]; // 1-indexed colour
        }
    }

    // fill dp array with +inf
   fill_n(&dp[0][0][0], MAXN*MAXN*MAXN, INF);
    
    // base case first tree is uncoloured
    if (!arr[0]) {
        // set costs to paint tree 0, colour j with beauty 1 = paintcost[i][j]
        for (int j = 1; j <= M; j++) {
            dp[0][1][j] = p[0][j];
        }
    } else { // if the tree is already coloured, set cost to 0 for that colour
        dp[0][1][arr[0]] = 0;
    }

    // dp table population
    // dp table represents the min cost
    // to paint tree i, with colour j, beauty k.

    for (int i = 1; i < N; i++) {
        for (int k = 1; k <= K; k++) {
            if (!arr[i]) {  // if tree i is not pre-coloured
                for (int j = 1; j <= M; j++) {
                    for (int oldJ = 1; oldJ <= M; oldJ++) {
                        if (j == oldJ) dp[i][k][j] = min(dp[i][k][j], dp[i-1][k][oldJ] + p[i][j]);
                        else dp[i][k][j] = min(dp[i][k][j], dp[i-1][k-1][oldJ] + p[i][j]);
                    }
                }
            } else {
                for (int oldJ = 1; oldJ <= M; oldJ++) {
                    if (arr[i] == oldJ) dp[i][k][arr[i]] = min(dp[i][k][arr[i]], dp[i-1][k][oldJ]);
                    else dp[i][k][arr[i]] = min(dp[i][k][arr[i]], dp[i-1][k-1][oldJ]);
                }
            }
        }
    }

    ll out = INF;
    for (int j = 1; j <= M; j++) {
        out = min(out, dp[N-1][K][j]);
    }

    cout << ((out >= INF) ? -1 : out ) << endl;

}
