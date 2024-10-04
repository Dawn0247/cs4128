#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = LLONG_MIN;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    // Reading satisfaction values for each dish
    vector<long long> satisfaction(n);
    for (int i = 0; i < n; ++i) {
        cin >> satisfaction[i];
    }

    // Create a 2D array to store bonuses between dishes
    vector<vector<long long>> bonus(n, vector<long long>(n, 0));
    for (int i = 0; i < k; ++i) {
        int x, y;
        long long c;
        cin >> x >> y >> c;
        bonus[x - 1][y - 1] = c;  // Using 0-based indexing
    }

    // DP table: dp[mask][i] represents the maximum satisfaction of eating the subset `mask` ending with dish `i`
    vector<vector<long long>> dp(1 << n, vector<long long>(n, INF));

    // Initialize: one dish in each subset
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = satisfaction[i];
    }

    // Iterate through all possible subsets
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            // If dish i is not in the subset `mask`, continue
            if (!(mask & (1 << i))) continue;

            // Try to add another dish j to the current subset
            for (int j = 0; j < n; ++j) {
                // If dish j is already in the subset `mask`, skip
                if (mask & (1 << j)) continue;

                int new_mask = mask | (1 << j);
                dp[new_mask][j] = max(dp[new_mask][j], dp[mask][i] + satisfaction[j] + bonus[i][j]);
            }
        }
    }

    // Find the maximum satisfaction for any subset of exactly `m` dishes
    long long max_satisfaction = INF;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) == m) {  // Check if the subset contains exactly m dishes
            for (int i = 0; i < n; ++i) {
                max_satisfaction = max(max_satisfaction, dp[mask][i]);
            }
        }
    }

    cout << max_satisfaction << endl;
    return 0;
}
