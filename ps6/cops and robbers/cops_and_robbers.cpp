#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 2500;
const int N = 35;
const ll INF = 1e18;
int terrain[26];
char grid[N][N];
int n, m, c;

struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;

    FlowNetwork(int n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge(int u, int v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge(int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    // constructs the level graph and returns whether the sink is still reachable
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0; // reset uptochild
            for (int v : adjList[u])
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) // already seen
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != -1;
    }

    // finds an augmenting path with up to f flow.
    ll augment(int u, int t, ll f) {
        if (u == t) return f; // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0) {
                // ignore edges not in the BFS tree.
                if (level[v] != level[u] + 1) continue;
                // revised flow is constrained also by this edge
                ll rf = augment(v,t,min(f, adjMat[u][v]));
                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u,v,rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s,t))
            for (ll x = augment(s,t,INF); x; x = augment(s,t,INF))
                res += x;
        return res;
    }
};

int main() {
    FlowNetwork g(MAX);
    cin >> n >> m >> c;
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
            g.add_edge(fromIn, fromOut, (cell >= 'a' && cell <= 'z') ? terrain[cell - 'a'] : INF);

            // if our cell is on the edge, connect to sink
            if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                g.add_edge(fromOut, sink, INF);
            }
            // connect to all other grids
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                
                if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    int newNode = ni * n + nj;
                    int toIn = 2 * newNode;
                    g.add_edge(fromOut, toIn, INF);
                }
            }

                        
        }
    }

    // for (int i = 0; i < 2 * n * m; i++) {
    //     for (auto u : edges[i]) {
    //         printf("%d goes to %d with weight %lld\n", i, u, weights[i][u]);
    //     }
    // }
    
    ll out = g.dinic(source, sink);
    cout << (out >= INF ? -1 : out)  << endl;
}
