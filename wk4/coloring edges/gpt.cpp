#include <iostream>
#include <vector>

using namespace std;

bool dfs(int node, const vector<vector<int>> &graph, vector<int> &visited, vector<int> &stack) {
    visited[node] = 1;  // Mark the node as being visited
    stack[node] = 1;    // Mark the node in the current recursion stack

    for (int neighbor : graph[node]) {
        if (visited[neighbor] == 0) {
            if (dfs(neighbor, graph, visited, stack)) {
                return true;
            }
        } else if (stack[neighbor] == 1) {
            return true;
        }
    }

    stack[node] = 0;  // Unmark the node from the current recursion stack
    return false;
}

bool has_cycle(int n, const vector<vector<int>> &graph) {
    vector<int> visited(n + 1, 0);
    vector<int> stack(n + 1, 0);

    for (int node = 1; node <= n; ++node) {
        if (visited[node] == 0) {
            if (dfs(node, graph, visited, stack)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        graph[u].push_back(v);
    }

    if (!has_cycle(n, graph)) {
        // The graph is a DAG, we can use 1 color
        cout << 1 << endl;
        for (int i = 0; i < m; ++i) {
            cout << 1 << " ";
        }
        cout << endl;
    } else {
        // The graph has cycles, we need 2 colors
        cout << 2 << endl;
        for (const auto &edge : edges) {
            if (edge.first < edge.second) {
                cout << 1 << " ";
            } else {
                cout << 2 << " ";
            }
        }
        cout << endl;
    }

    return 0;
}