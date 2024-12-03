#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;
const int MAXN = 100005;
const ll LL_INF = 1e18;
const int I_INF = 1e9;
int n,m,k;
struct Edge {
    int u;  // from
    int v;  // to
    ll  w;  // weight
};

struct state {
    int u;
    int v;
    ll  w;
    int d;
    int m;
    
    bool operator < (const state &other) const {
        return (other.w == w) ? other.d < d : other.w < w ;
    }

};

ll dist[MAXN] = {0};
int pred[MAXN] = {0};
bool seen[MAXN] = {0};
vector<Edge> edges[MAXN];
priority_queue<state> pq;

void dijkstra (int s) {
    pq.push({0, s, 0, 1, I_INF}); // distance to s itself is zero
    while (!pq.empty()) {
        // choose (d, v) so that d is minimal
        // i.e. the closest unvisited vertex
        state cur = pq.top();
        pq.pop();
        int u = cur.v;
        ll d = cur.w;
        if (seen[u]) continue;
        dist[u] = d;
        seen[u] = true;
        pred[u] = cur.u;
        // relax all edges from v
        for (Edge nxt : edges[u]) { 
            int v = nxt.v, weight = nxt.w;
            ll nw = d;
            int nm = cur.m;
            if (nm > weight) nm = weight;
            if (cur.d > k) nw += nm; 
            if (!seen[v]) pq.push({u, v, nw, cur.d+1, nm});
        }
    }
}

int main() {
    cin >> n >> m >> k;
    int u,v,w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edges[u].push_back({u, v, w});
    }

    dijkstra(1);
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    } cout << endl;

    for (int i = 1; i <= n; i++) {
        cout << pred[i] << ' ';
    } cout << endl;
    cout << ((pred[n] == 0) ? -1 : dist[n]) << endl;
    cerr << n << ' ' << m << ' ' << k;
}