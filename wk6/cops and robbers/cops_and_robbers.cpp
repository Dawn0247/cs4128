#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 2500;
const int N = 35;
const int INF = 1e9;
int capacity[MAX][MAX], level[MAX];
int terrain[26];
char grid[N][N];
vector<int> edges[MAX];
int n, m, c;

bool bfs(int source, int sink) {
    fill(level, level + MAX, -1);
    queue<int> q;
    q.push(source);
    level[source] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : edges[u]) {
            if (level[v] == -1  && capacity[u][v] > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    } return level[sink] != -1;
}

int dfs(int u, int flow, int sink) {
    if (u == sink) return flow;
    for (int v : edges[u]) {
        if (level[v] == level[u] + 1 && capacity[u][v] > 0) {
            int curFlow = min(flow, capacity[u][v]);
            int tmpFlow = dfs(v, curFlow, sink);
            if (tmpFlow > 0) {
                capacity[u][v] -= tmpFlow;
                capacity[v][u] += tmpFlow;
                return tmpFlow;
            }
        }
    }
    return 0;
}

int dinic(int source, int sink) {
    int totalFlow = 0;
    while (bfs(source, sink)) {
        while (int flow = dfs(source, INF, sink)) {
            totalFlow += flow;
        }
    }
    return totalFlow;
}


int main() {
    cin >> n >> m >> c;
    fill_n(&capacity[0][0], MAX*MAX, 0);
    int source = -1;
    int sink = MAX - 1;
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < c; i++) {
        cin >> terrain[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int node = i * n + j;
            char cell = grid[i][j];
            if (cell == 'B') {
                source = 2 * node;
            }
            int fromIn = 2 * node, fromOut = 2 * node + 1;
            // vertex capacity
            edges[fromIn].push_back(fromOut);
            capacity[fromIn][fromOut] = (cell >= 'a' && cell <= 'z') ? terrain[cell - 'a'] : INF;

            // if our cell is on the edge, connect to sink
            if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                edges[fromOut].push_back(sink);
                capacity[fromOut][sink] = INF;

            }
            // connect to all other grids
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                
                if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    int newNode = ni * n + nj;
                    int toIn = 2 * newNode;
                    edges[fromOut].push_back(toIn);
                    capacity[fromOut][toIn] = INF;
                }
            }

                        
        }
    }

    // for (int i = 0; i < 2 * n * m; i++) {
    //     for (auto u : edges[i]) {
    //         printf("%d goes to %d with weight %d\n", i, u, capacity[i][u]);
    //     }
    // }
    
    int out = dinic(source, sink);
    cout << (out >= INF ? -1 : out)  << endl;

}