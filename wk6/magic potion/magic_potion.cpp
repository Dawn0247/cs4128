#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 1005; //TODO: fix limits
const ll INF = 1e18;
ll weights[MAX][MAX], level[MAX], uptochild[MAX];
vector<ll> edges[MAX];
int n, m, k;

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
    cin >> n >> m >> k;
    FlowNetwork g(MAX);
    ll source = MAX - 1;
    ll sink = MAX - 2;
    ll potions = MAX - 3;
    ll heros = MAX - 4;
    // heros: 1 to n
    // monsters n to n+m
    int x, y;
    // hero to monster
    for (int i = 1; i <= n; i++) {
        cin >> x;
        for (int j = 1; j <= x; j++) {
            cin >> y;
            g.add_edge(i, n+y, 1);
        }
    }
    // source to potion source
    g.add_edge(source, potions, k);
    g.add_edge(source, heros, n);

    for (int i = 1; i <= n; i++) {
        // heros ability to hero
        g.add_edge(heros, i, 1);
        // potion source to hero
        g.add_edge(potions, i, 1);
    }

    // monster to sink
    for (int i = 1; i <= m; i++) {
        g.add_edge(n+i, sink, 1);   
    }

    cout << g.dinic(source, sink) << endl;
}