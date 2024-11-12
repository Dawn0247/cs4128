#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define pll pair<ll, ll>
#define pii pair<int, int>
#define debugArr(arr, n) for(int _i = 0; _i < n; _i++) cout << arr[_i] << ' '; cout << endl
#define debugPairArr(arr, n) for(int _i = 0; _i < n; _i++) cout << arr[_i].first << ' ' << arr[_i].second << '\n'
#define debug(x) cout << "DEBUG: " << x << endl

struct edge {
    int u;  // from
    int v;  // to
    ll  w;  // weight
    int p;  // priority
    int f;  // is erasable
    bool operator < (const edge &other) const {
        return (other.w == w) ? other.p < p : other.w < w ;
    }
};
const int N = 100005;
const ll INF = 1e18;
vector<edge> edges[N];
pii pred[N];
ll dist[N];
priority_queue<edge> pq;
int n, m, L, s, t;

void dijkstras(int s) {
    fill(pred, pred + N, make_pair(-1, 0));    
    fill(dist, dist+N, 0);
    pq.push({-1, s, 0, 0, 0});
    while (!pq.empty()) {
        edge cur = pq.top(); pq.pop();
        if (pred[cur.v].first != -1) continue;
        dist[cur.v] = cur.w;
        pred[cur.v] = {cur.u, cur.f};
        // cout << cur.u << endl;
        for (edge nxt : edges[cur.v]) {
            if (pred[nxt.v].first == -1) pq.push({nxt.u, nxt.v, cur.w + nxt.w, cur.p + nxt.p, nxt.f});
        }
    }
}


int main() {
    cin >> n >> m >> L >> s >> t;
    int x, y, z;

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        edges[x].push_back({x, y, (z ? z : 1), 1, (z ? 0 : 1)});
        edges[y].push_back({y, x, (z ? z : 1), 1, (z ? 0 : 1)});
    }
    
    // for (int i = 0; i < n; i++) {
    //     for (edge e : edges[i]) {
    //         printf("%d %d %lld %d\n", e.u, e.v, e.w, e.f);
    //     }  
    // }


    dijkstras(s);
    if (dist[t] > L || dist[t] == 0) {
        cout << "NO" << endl;
        return 0;
    }

    // for (int i = 0; i < n; i++) {
    //     cout << pred[i].first << ' ' << pred[i].second << " | "; 
    // } cout << endl;

    ll diff = L - dist[t];

    int bt = t;
    int diffEdge = -1;
    
    while (bt != s) {
        if (pred[bt].second) {
            diffEdge = bt;
        }
        bt = pred[bt].first;
    }

    if (diffEdge != -1) {
        int targetU = pred[diffEdge].first;
        int targetV = diffEdge;
        
        for (int i = 0; i < n; i++) {
            for (auto it = edges[i].begin(); it != edges[i].end(); it++) {
                edge e = *it;
                if ( (e.u == targetU && e.v == targetV) || (e.u == targetV && e.v == targetU) )  {
                    it->w = 1 + diff;
                } else if (e.f == 1) {
                    it->w = INF;
                }
            }
        }

        bt = t;
        while (bt != s) {
            if (pred[bt].second) {
                int tv = bt;
                int tu = pred[bt].first;
                if (tv == diffEdge) break;
                for (int i = 0; i < n; i++) {
                    for (auto it = edges[i].begin(); it != edges[i].end(); it++) {
                        edge e = *it;
                        if ( (e.u == tu && e.v == tv) || (e.u == tv && e.v == tu) )  {
                            it->w = 1;
                        }
                    }
                }
            }
            bt = pred[bt].first;
        }
    }

    dijkstras(s);

    // for (int i = 0; i < n; i++) {
    //     cout << dist[i] << ' ';
    // }   cout << endl;

    if (dist[t] != L) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (edge e : edges[i]) {
                if (e.v > e.u) {
                    cout << e.u << ' ' << e.v << ' ' << e.w << '\n';
                }
            }
        }
    }
    
}