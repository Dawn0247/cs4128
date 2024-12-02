#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN = 21;
const int MOD = 1e9 + 7;
ll dp[MAXN][1<<MAXN] = {0};
int words[MAXN][26];
string target;
int n, k;

int main() {    
    cin >> n >> k;
    cin >> target;
    string word;
    for (int i = 0; i < n; i++) {
        cin >> word;
        for (char c : word) {
            words[i][c-'a']++;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (auto k : words[i]) {
    //         cout << k << ' ';
    //     } cout << endl;
    // }

    // base case
    dp[0][0] = 1;

    for (int toId = 1; toId <= k; toId++) {
        for (int fromMask = 0; fromMask < (1 << n); fromMask++) {
            for (int wordId = 0; wordId < n; wordId++) {
                int toMask = ( fromMask | (1 << wordId) );
                if (toMask == fromMask) continue;
                dp[toId][toMask] += (dp[toId-1][fromMask]%MOD * words[wordId][target[toId-1] -'a']%MOD)%MOD;
                dp[toId][toMask] %= MOD;
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int m = 0; m < (1 << n); m++) {
    //         cout << dp[i][m] << ' ';
    //     } cout << endl;
    // }   
    ll out = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        out += dp[k][mask];
        out %= MOD;
    }

    cout << out << endl;
}