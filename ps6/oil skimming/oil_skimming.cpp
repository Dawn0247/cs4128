#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 605; //TODO: fix limits
const ll INF = 1e18;
const int DXY[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n, m, k;
string grid[MAX];

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

int flowGraph(int n) {
    FlowNetwork g(n * n + 2);
    int source = n * n;
    int sink = n * n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                int node = i * n + j;

                if ((i + j) % 2 == 0) {
                    g.add_edge(source, node, 1);
                
                    for (auto [di, dj] : DXY) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == '#') {
                            int next = ni * n + nj;
                            g.add_edge(node, next, 1);
                        } 
                    }
                } else {
                    g.add_edge(node, sink, 1);
                }
            }
        }
    }

    return g.dinic(source, sink);

}
int main() {
    cin >> k;
    for (int c = 1; c <= k; c++) {
        int n;
        cin >> n;
        for (int i = 0; i<n; i++) {
            cin >> grid[i];
        }

        int out = flowGraph(n);
        cout << "Case " << c << ": " << out << endl;

        
    }

}