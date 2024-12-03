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
const ll INF = 1e18;
struct Edge {
    int u, v;
    ll w;
};
vector<Edge> edges;
ll dist[MAXN][MAXN];
int n;

void floydWarshall() {
    fill_n(&dist[0][0], MAXN*MAXN, INF);

    for (Edge e : edges)
        dist[e.u][e.v] = e.w;

    for (int u = 0; u < n; ++u)
        dist[u][u] = 0;

    for (int i = 0; i < n; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
                dist[v][u] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
}

int main() {
    int m; // Number of edges
    cin >> n >> m;

    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    floydWarshall();

    // Optional: Print the distance matrix
    cout << "Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}