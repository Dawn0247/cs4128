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
            if (size[rootX] > size[rootY]) std::swap(rootX, rootY);
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
    }
};

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<Edge> edges;
int n, m;

// Kruskal's Algorithm using DSU
vector<Edge> kruskal() {
    DSU dsu(n);
    sort(edges.begin(), edges.end());

    vector<Edge> mst;

    for (auto edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    return mst;
}

int main() {
    DSU d = DSU(10);
    d.unite(0,1);
    d.unite(1,2);
    d.unite(2,3);
    debug(d.find(3));
    d.unite(5,6);
    d.unite(6,7);
    d.unite(7,8);
    debug(d.find(7));
    d.unite(2,7);
    debug(d.find(3));
    debug(d.find(7));

    cin >> m >> n;
    int u, v, w;
    for (int i = 0; i < n; i++) {
        cin >> u >> v >> w;
        edges.push_back({u,v,w});
    }
    for (auto [u,v,w] : edges) {
        printArr(3, vector<int>({u,v,w}));
    }
    auto mst = kruskal();

    cout << "Edges in MST:\n";
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << "\n";
    }
    return 0;
}
