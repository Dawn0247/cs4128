#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int, int>

const int N = 200005;
const ll INF = 1e18;
set<int> edges[N];
bool visited[N];
int n, k;


bool bfs(int s) {
    queue<pii> q;
    q.emplace(s, 0);
    visited[s] = true;

    while (!q.empty()) {
        auto [v, depth] = q.front();
        q.pop();

        // reached the end
        if (v == 0) {
            return true;
        } 

        // under water
        if ( (( v > n ) ? v - n : v) <= depth ) {
            continue;
        }

        for (int e : edges[v]) {
            if (!visited[e]) {
                visited[e] = true;
                q.emplace(e, depth+1);

            }
        }
    }

    return false;
}

int main() {
    string l, r;
    cin >> n >> k;
    cin >> l >> r;

    // left wall has ind 1 to n
    // right wall has index n+1 to 2n
    // 0 is the super sink

    string wall = " " + l + r;
    
    // left wall
    for (int i = 1; i <= n; i++) {
        if (wall[i] == 'X') continue;
        // up
        if (i+1 > n) edges[i].insert(0);                         // if escape, connect to super sink
        else if (wall[i+1] == '-') edges[i].insert(i+1);         // if still on map

        // down
        if (i > 1 && wall[i-1] == '-') edges[i].insert(i-1);     // skip if not on map.

        // swap
        if (n+i+k > 2*n) edges[i].insert(0);                     // if escape, connect to super sink
        else if (wall[n+i+k] == '-') edges[i].insert(n+i+k);     // if still on map
    }

    // right wall
    for (int i = n + 1; i <= 2*n; i++) {
        if (wall[i] == 'X') continue;
        // up
        if (i+1 > 2*n) edges[i].insert(0);                       // if escape, connect to super sink
        else if (wall[i+1] == '-') edges[i].insert(i+1);         // if still on map

        // down
        if (i > n + 1 && wall[i-1] == '-') edges[i].insert(i-1); // skip if not on map.

        // swap
        if (i+k-n > n) edges[i].insert(0);                       // if escape, connect to super sink
        else if (wall[i+k-n] == '-') edges[i].insert(i+k-n);     // if still on map
    }

    cout << (bfs(1) ? "YES" : "NO") << endl;

}