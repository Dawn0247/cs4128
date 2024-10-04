
#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define ll long long 
const int MAXN = 101;
int N, M, K;
ll arr[MAXN];
ll paint[MAXN][MAXN];
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
        for (int j = 0; j < M; j++) {
            cin >> paint[i][j];
        }
    }
    

    // dp: min cost for 
    // i: first i trees
    // j: colour of the i'th tree
    // k: number of beauty groups
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < K; k++) {
                if (!arr[i]) {
                    for (int )

                }

            }
        }
    }










    for (int i = 0; i < N; i++) {
        cout << arr[i] << ' ';
    } cout << '\n';

    // paint[i][j] = cost paint tree i into color j
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << paint[i][j] << ' ';
        } cout << '\n';
    }



}
