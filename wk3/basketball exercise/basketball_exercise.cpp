#include <bits/stdc++.h>
using namespace std;

#define ll long long 
const int MAXN = 10e5+5;
ll arr[2][MAXN];
ll dp[2][MAXN];

ll solve(int i, int r) {
    // base case
    if (i < 0) {
        return 0;
    }
    if (i == 0) { 
        return arr[r][i];
    }

    //dp
    if (dp[r][i]) {
        return dp[r][i];
    }

    // recur
    ll out = max(solve(i-2, 1-r), solve(i-1, 1-r)) + arr[r][i];
    dp[r][i] = out;
    return out;
}
int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    int N;
    cin >> N;

    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }

    cout << max(solve(N-1, 0), solve(N-1, 1)) << endl;
}
