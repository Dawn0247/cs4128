#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Edge {
    int from, to, weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int getWeight(int u, int v) {
    for (Edge e 
}

struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

struct LCA {
    int n, maxLog;
    vector<Edge> adj[100005];  // adjacency list of the tree with edges (array of vectors)
    vector<vector<int>> up;    // up[i][j] stores the 2^j-th ancestor of node i
    vector<int> depth;         // stores the depth of each node

    LCA(int n) {
        this->n = n;
        maxLog = ceil(log2(n));
        up.assign(n + 1, vector<int>(maxLog + 1, -1));
        depth.resize(n + 1);
    }

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(u, v, w);
        adj[v].emplace_back(v, u, w);
    }

    void dfs(int node, int parent) {
        up[node][0] = parent; // direct parent
        for (int i = 1; i <= maxLog; i++) {
            if (up[node][i - 1] != -1) {
                up[node][i] = up[up[node][i - 1]][i - 1];
            }
        }
        for (const Edge& edge : adj[node]) {
            int neighbor = edge.to;
            if (neighbor != parent) {
                depth[neighbor] = depth[node] + 1;
                dfs(neighbor, node);
            }
        }
    }

    void preprocess(int root) {
        depth[root] = 0;
        dfs(root, -1);
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        // Lift u to the same depth as v
        int diff = depth[u] - depth[v];
        for (int i = 0; i <= maxLog; i++) {
            if ((diff >> i) & 1) {
                u = up[u][i];
            }
        }

        if (u == v) {
            return u;
        }
        int mxm = 0;
        // Lift both u and v until their ancestors match
        for (int i = maxLog; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }
};


int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;

    // Reading edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        edges.emplace_back(u, v, w);
    }

    // Finding MST using Kruskal's algorithm
    sort(edges.begin(), edges.end(), compareEdges);
    DSU dsu(n);
    LCA lca(n);

    for (const Edge& edge : edges) {
        if (dsu.find(edge.from) != dsu.find(edge.to)) {
            dsu.unite(edge.from, edge.to);
            lca.addEdge(edge.from, edge.to, edge.weight);
        }
    }

    // Preprocessing to set up the binary lifting table
    lca.preprocess(0); // assuming 0 is the root (1 in 1-based index)

    // Queries
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        cout << "LCA of " << (u + 1) << " and " << (v + 1) << ": " << (lca.getLCA(u, v) + 1) << endl;
    }

    return 0;
}
