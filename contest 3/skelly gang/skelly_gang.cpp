#include <bits/stdc++.h>
using namespace std;

// Edge struct to store edges (u, v, w)
struct Edge {
    int u, v, weight, p;
};

vector<Edge> adjList;
vector<Edge> allEdges;
vector<pair<int, int>> mstEdges;
// union find
struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
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

// kruskals
void kruskal(int n) {
    sort(adjList.begin(), adjList.end(), [](const Edge& a, const Edge& b) {
        return (a.weight == b.weight) ? a.p > b.p : a.weight < b.weight;
    });

    DSU dsu(n);
    int mstWeight = 0;

    for (auto &edge : adjList) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mstEdges.push_back({u, v});
            mstWeight += weight;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int x, y, z;
    
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        Edge e = {x-1, y-1, z, i};
        allEdges.push_back(e);
    }
    set<pair<int, int>> oldMst, newMst;
    adjList = allEdges;
    kruskal(n);
    for (auto [a, b] : mstEdges) {
        oldMst.insert({a, b});
    }
    allEdges[0].weight = 0;
    adjList = allEdges;
    mstEdges.clear();
    kruskal(n);
    for (auto [a, b] : mstEdges) {
        newMst.insert({a, b});
    }

    set<pair<int, int>> diff;
    set_difference(oldMst.begin(), oldMst.end(), newMst.begin(), newMst.end(), inserter(diff, diff.begin()));
    cout << !diff.empty() << endl;



}