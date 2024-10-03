#include <bits/stdc++.h>
using namespace std;

#define ll long long 
const int MAXN = 20;
int N, M, K;
ll arr[MAXN];
ll dp[MAXN][MAXN][MAXN];
ll bonuses[MAXN][MAXN];



// i: curr ind of food
// c: capacity left
// p: previous food eaten
ll solve(int i, int c, int p) {

}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    for(int i = 0; i < K; i++) {
        int d1, d2, bonus;
        cin >> d1 >> d2 >> bonus;
        bonuses[d1][d2] = bonus;
    } 

    fill_n(&dp[0][0][0], MAXN * MAXN * MAXN, -1);

    for (int i = 0; i <= N; i++) {
        cout << arr[i] << ' ';
    } cout << endl;

    for (auto kv : bonusMap) {
        cout << kv.first << ": " << kv.second << endl;
    }

    cout << solve(N, M, 0);

}
