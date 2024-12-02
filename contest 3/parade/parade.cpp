#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

struct Edge {
    int to, color, cost, mask;
};

struct State {
    int node, mask, ex;
    bool operator>(const State& other) const {
        return ex > other.ex;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> elev(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> elev[i];
    }

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        int cost = max(0, elev[v] - elev[u]);                       // uphill cost only
        adj[u].push_back({v, c - 1, cost});                         // color is zero-indexed
        adj[v].push_back({u, c - 1, max(0, elev[u] - elev[v])});    // bidirectional
    }

    int full_mask = (1 << k) - 1;
    vector<vector<int>> dist(n + 1, vector<int>(1 << k, INF));
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1][0] = 0;
    pq.push({1, 0, 0});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int node = current.node;
        int colors_mask = current.mask;
        int exhaustion = current.ex;

        if (node == n && colors_mask == full_mask) {
            cout << exhaustion << endl;
            return 0;
        }

        if (exhaustion > dist[node][colors_mask]) continue;

        for (Edge& edge : adj[node]) {
            int next_node = edge.to;
            int next_color = edge.color;
            int next_cost = exhaustion + edge.cost;
            int next_mask = colors_mask | (1 << next_color);

            if (next_cost < dist[next_node][next_mask]) {
                dist[next_node][next_mask] = next_cost;
                pq.push({next_node, next_mask, next_cost});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}