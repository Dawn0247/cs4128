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


const int MAXN = 1e5 + 5;  // Maximum number of nodes
const int MAXLOG = 17;        // log2(MAXN) is around 17 for MAXN = 1e5

vector<int> edges[MAXN];
int parent[MAXN][MAXLOG];         // up[v][j] is the 2^j-th ancestor of node v
int depth[MAXN];

void dfs(int v, int p) {
    parent[v][0] = p;  // The first ancestor (2^0) is the parent
    for (int j = 1; j < MAXLOG; j++) {
        if (parent[v][j - 1] != -1)
            parent[v][j] = parent[parent[v][j - 1]][j - 1];
        else
            parent[v][j] = -1;
    }
    for (int u : edges[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    // Lift u up to the same level as v
    int diff = depth[u] - depth[v];
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if ((diff >> j) & 1)
            u = parent[u][j];
    }

    if (u == v)
        return u;

    // Lift u and v up until we find the LCA
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if (parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }

    return parent[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;  // number of nodes
    cin >> n;
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    fill_n(&parent[0][0], MAXN*MAXLOG, -1);
    depth[0] = 0;
    dfs(0, -1);  // Assuming node 0 is the root

    int q;  // number of queries
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        debug(lca(u, v));
    }

    return 0;
}
