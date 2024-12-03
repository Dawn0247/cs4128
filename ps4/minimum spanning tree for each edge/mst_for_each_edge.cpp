#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll,ll>
#define repRange(x,y,i) for (int i = x; i < y; i++)
#define printArr(n, arr) repRange(0, n, i) { cerr << arr[i] << ' '; } cerr << endl
#define print2DArr(n, m, arr) repRange(0, n, j) { printArr(m, arr[j]); }
#define printPairArr(n, arr) repRange(0, n, i) { cerr << arr[i].first << ' ' << arr[i].second << '\n'; };
#define debug(var) cerr << #var << ": " <<  var << endl
#define flag(i) cerr << "Flag: " << i << endl;

using namespace std;


const int MAXN = 1e5 + 5;  // Maximum number of nodes
const int MAXLOG = 17;        // log2(MAXN) is around 17 for MAXN = 1e5

vector<int> edges[MAXN];
map<ll, ll> edgeWeightMap;
int parent[MAXN][MAXLOG];         // up[v][j] is the 2^j-th ancestor of node v
ll maxWeights[MAXN][MAXLOG] = {0};
int depth[MAXN];



struct DSU {
    std::vector<int> parent, size;

    DSU(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }

    void unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] > size[rootY]) swap(rootX, rootY);
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
    }
};

struct Edge {
    int u, v; 
    ll weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<Edge> allEdges;
int n, m;

// Kruskal's Algorithm using DSU
vector<Edge> kruskal() {
    DSU dsu(m);
    vector<Edge> krusEdges = vector<Edge>(allEdges);
    sort(krusEdges.begin(), krusEdges.end());

    vector<Edge> mst;

    for (auto edge : krusEdges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    return mst;
}

ll cantors(int x, int y) {
    return ((x+y)*(x+y+1))/2 + x*y;
}   

ll getMaxWeight(int u, int v) {
    return edgeWeightMap[cantors(u, v)];
}

void dfs(int v, int p) {
    parent[v][0] = p;  // The first ancestor (2^0) is the parent
    maxWeights[v][0] = edgeWeightMap[cantors(p, v)];
    for (int j = 1; j < MAXLOG; j++) {
        if (parent[v][j - 1] != -1) {
            parent[v][j] = parent[parent[v][j - 1]][j - 1];
            if (parent[v][j] != -1) maxWeights[v][j] = max( maxWeights[v][j-1], maxWeights[parent[v][j-1]][j-1] );
        } else {
            parent[v][j] = -1;
            // maxWeights[v][j] = 0;
        }
    }
    for (int u : edges[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

ll lca(int u, int v) {
    ll maxWeight = 0;
    if (depth[u] < depth[v])
        swap(u, v);

    // Lift u up to the same level as v
    int diff = depth[u] - depth[v];
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            maxWeight = max(maxWeight, maxWeights[u][j]);
            u = parent[u][j];        
            // flag(1);    
        }
    }

    if (u == v) return maxWeight;

    // Lift u and v up until we find the LCA
    for (int j = MAXLOG - 1; j >= 0; j--) {
        maxWeight = max(maxWeight, maxWeights[u][j]);
        maxWeight = max(maxWeight, maxWeights[v][j]);
        if (parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
            // printArr(3, vector<int>({u,v,j}));
            // debug(maxWeight);
        }
    }

    return maxWeight;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        allEdges.push_back({u-1, v-1, w});
    }

    vector<Edge> mst = kruskal();
    ll mstWeight = 0;
    for (auto [u,v,w] : mst) {
        // cout << u << ' ' << v << ' ' << w << '\n';
        edges[u].push_back(v);
        edges[v].push_back(u);
        edgeWeightMap[cantors(u,v)] = w;
        mstWeight += w;
    }   

    fill_n(&parent[0][0], MAXN*MAXLOG, -1);
    depth[0] = 0;
    dfs(0, -1);  // Assuming node 0 is the root

    // print2DArr(n, 6, maxWeights);
    // cout << "PARENTS:\n";
    // print2DArr(n, 6, parent);

    // debug(lca(0, 1));
    // debug(lca(0, 2));
    // debug(lca(0, 3));
    // debug(lca(1, 2));
    // debug(lca(1, 4));
    // debug(lca(2, 3));
    // debug(lca(3, 4));

    // debug(lca(1,6));
    // debug(lca(6,1));
    for (Edge e : allEdges) {
        ll mxm = lca(e.u, e.v);
        if (mxm != e.weight) cout <<  mstWeight - mxm + e.weight << endl;
        else cout << mstWeight << endl;
    }


    return 0;
}
