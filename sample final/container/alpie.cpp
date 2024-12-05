#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll INF = 2e6+7; 
int l;
int w;
int h;
ll a;
ll b;
int c;
int n;
int sink;
int src;

struct Delta {
    int dx;
    int dy;
    int dz;
};

struct container {
    int x;
    int y;
    ll z;
};

vector<container> containers;

struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;

    FlowNetwork() {};

    FlowNetwork (int _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (int u, int v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge (int u, int v, ll c) {
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

    ll augment(int u, int t, ll f) {
        if (u == t) return f; // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0) {
                // ignore containers not in the BFS tree.
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

FlowNetwork fn;
pair<Delta, int> DXY[6] = { {{0, 1, 0}, 0}, {{0, -1, 0}, 0}, 
                            {{1, 0, 0}, 0}, {{-1, 0, 0}, 0}, 
                            {{0, 0, -1}, 0}, {{0, 0, 1}, 0} };

void makeCntEdges(int x, int y, ll z) {
    for (auto [d, weight] : DXY) {
        int newx = x + d.dx;
        int newy = y + d.dy;
        int newz = z + d.dz;
        
        int current = x + (l * y) + (l * w * z);
        int next = newx + (l * newy) + (l * w * newz);

        if (newx >= 0 && newx < l && newy >= 0 && newy < w && newz >= 0 && newz < h) {
            fn.add_edge(current, next, weight);
        } else {
            fn.add_edge(current, sink, weight);
        }
    }
}

int main() {
    cin >> l;
    cin >> w;
    cin >> h;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> n;

    DXY[0].second = b;
    DXY[1].second = b;
    DXY[2].second = a;
    DXY[3].second = a;
    DXY[4].second = c;
    DXY[5].second = c;

    for (int i = 0; i < n; i++) {
        int x;
        int y;
        int z;
        cin >> x;
        cin >> y;
        cin >> z;
        containers.push_back({x, y, z});
    }

    src = (l * w * h) + 2;
    sink = (l * w * h) + 4;
    fn = FlowNetwork((l * w * h) + 7);

    for (int x = 0; x < l; x++) {
        for (int y = 0; y < w; y++) {
            for (int z = 0; z < h; z++) {
                makeCntEdges(x, y, z);
            }
        }
    }

    for (auto c : containers) {
        fn.add_edge(src, c.x + (l * c.y) + (l * w * c.z), INF);
    }

    for (auto r : fn.adjMat) {
        for (auto w : r) {
            cout << w << ' ';
        }   cout << endl;
    }

    cout << fn.dinic(src, sink) << '\n';
}