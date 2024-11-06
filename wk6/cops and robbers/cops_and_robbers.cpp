#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 1225;
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
            char fromCell = grid[i][j];
            if (fromCell == 'B') {
                source = node;
            }

            // if our cell is on the edge, connect to sink
            if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                edges[node].push_back(sink);
                capacity[node][sink] = INF;
            }
            // connect to all other grids
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    int neighbour = ni * n+ nj;
                    char toCell = grid[ni][nj];
                    edges[node].push_back(neighbour);
                    capacity[node][neighbour] = (toCell >= 'a' && toCell <= 'z') ? terrain[toCell - 'a'] : INF;
                }
            }

                        
        }
    }
    
    int out = dinic(source, sink);
    cout << (out >= INF ? -1 : out)  << endl;

}