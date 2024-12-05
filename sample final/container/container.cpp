#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll,ll>
#define repRange(x,y,i) for (int i = x; i < y; i++)
#define printArr(n, arr) repRange(0, n, i) { cerr << arr[i] << ' '; } cerr << endl
#define print2DArr(n, m, arr) repRange(0, n, j) { printArr(m, arr[j]); }
#define printPairArr(n, arr) repRange(0, n, i) { cerr << arr[i].first << ' ' << arr[i].second << '\n'; };
#define debug(var) cerr << #var << ": " <<  var << endl
#define flag(i) cerr << "Flag: " << i
using namespace std;

const int MAXN = 1005;
const int N = 11;
const ll INF = 1e18;


struct Delta {
    int dx, dy, dz; 
};

struct Cell {
    int x, y, z;
};



struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;
    FlowNetwork() {}

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


pair<Delta, int> deltas[6] = {  {{1,0,0}, 0}, {{-1,0,0}, 0},
                                {{0,1,0}, 0}, {{0,-1,0}, 0},
                                {{0,0,1}, 0}, {{0,0,-1}, 0} };

vector<Cell> boxes;
int l, w, h, n;
int src, snk;
FlowNetwork g;


bool onBorder(Cell b, Delta d) {
    if (b.x + d.dx >= l || b.x + d.dx < 0)  return true;
    if (b.y + d.dy >= w || b.y + d.dy < 0)  return true;
    if (b.z + d.dz >= h || b.z + d.dz < 0)  return true;
    return false;
}

Cell applyDelta(Cell b, Delta d) {
    return {b.x + d.dx, b.y + d.dy, b.z + d.dz};
}

int toId(Cell b) {
    return b.x + l*b.y + l*w*b.z;
}

void constructOutEdge(Cell b) {
    for (auto [d, w] : deltas) {
        if (onBorder(b, d)) {
            g.add_edge(toId(b), snk, w);
        } else {
            g.add_edge(toId(b), toId(applyDelta(b, d)), w);
        }

    }
}


int main() {
    int a,b,c;
    cin >> l >> w >> h >> a >> b >> c >> n;
    deltas[0].second = a;
    deltas[1].second = a;
    deltas[2].second = b;
    deltas[3].second = b;
    deltas[4].second = c;
    deltas[5].second = c;

    g = FlowNetwork(l*w*h + 2);

    src = l*w*h;
    snk = l*w*h + 1;
    for (int x = 0; x < l; x++) {
        for (int y = 0; y < w; y++) {
            for (int z = 0; z < h; z++) {
                constructOutEdge({x,y,z});
            }
        }
    }

    int x, y, z;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> z;
        g.add_edge(snk, toId({x,y,z}), INF);
    }

    for (int from = 0; from < g.adjList.size(); from++) {
        for (ll to : g.adjList[from]) {
            cerr << from << ' ' << to << ' ' << g.adjMat[from][to] << endl;
        }
    }
    
    
}
