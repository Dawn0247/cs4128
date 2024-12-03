#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define pll pair<ll, ll>
#define pii pair<int, int>
#define debugArr(arr, n) for(int _i = 0; _i < n; _i++) cout << arr[_i] << ' '; cout << endl
#define debugPairArr(arr, n) for(int _i = 0; _i < n; _i++) cout << arr[_i].first << ' ' << arr[_i].second << " | "; cout << '\n';
#define debug(x) cout << "DEBUG: " << x << endl
#define printPair(p) cout << #p << ": " << p.first << ' ' << p.second << endl

struct Edge {
    int u;  // from
    int v;  // to
    ll  w;  // weight
    int p;  // priority
    int f;  // is erasable
    bool operator < (const Edge &other) const {
        return (other.w == w) ? other.p < p : other.w < w ;
    }
};
const int M = 100005;
const int N = 1005;
const ll INF = 1e15;
vector<Edge> edges[M];
ll weights[N][N] = {0};
pii pred[N];
ll dist[N];
priority_queue<Edge> pq;
int n, m, L, s, t;

void dijkstras(int s, int t) {
    fill(pred, pred + N, make_pair(-1, 0));    
    fill(dist, dist+N, 0);
    pq.push({-1, s, 0, 0, 0});
    while (!pq.empty()) {
        Edge cur = pq.top(); pq.pop();
        if (pred[cur.v].first != -1) continue;
        dist[cur.v] = cur.w;
        pred[cur.v] = {cur.u, cur.f};
        if (cur.u == t) return;
        // cout << cur.u << endl;
        for (Edge nxt : edges[cur.v]) {
            if (pred[nxt.v].first == -1) pq.push({nxt.u, nxt.v, cur.w + weights[nxt.u][nxt.v], cur.p + nxt.p, nxt.f});
        }
    }
}
bool work() {
    dijkstras(s, t);
    if (dist[t] > L || dist[t] == 0) {
        return 0;
    }

    ll diff = L - dist[t];
    // debugArr(dist, n);
    // debugPairArr(pred, n);

    // fuckfuckfuckfuckfuckfuckfuckfuckfuckfuck
    for (int i = 0; i < n; i++) {
        for (Edge e : edges[i]) {
            if (e.f) {
                weights[e.u][e.v] = INF;
                weights[e.v][e.u] = INF;
            }
        }
    }
    
    // set current path to 1's
    int u = t, v;
    while (u != s) {
        v = pred[u].first;
        if (pred[u].second) {
            weights[u][v] = 1;
            weights[v][u] = 1;
        }
        u = v;
    }

    // check if current path is valid
    pii oldPred[N];
    copy(pred, pred+N, oldPred);
    u = t;
    while (u != s) {
        
        v = oldPred[u].first;
        if (oldPred[u].second) {
            weights[u][v] += diff;
            weights[v][u] += diff;
            
            dijkstras(s, t);
            if (dist[t] == L) {
                break;
            }

            dijkstras(u, v);


            weights[u][v] = dist[v];
            weights[v][u] = dist[v];
            diff -= (dist[v] - 1);

        }
        u = v;
    }

    // printPair(bt);

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << weights[i][j] << ' ';
    //     }cout << endl;
    // }

    // for (int i = 0; i < n; i++) {
    //     for (edge e : edges[i]) {
    //         printf("%d to %d with weight %lld\n", e.u, e.v, e.w);
    //     }
    // }



    if (dist[t] < L) {
        return 0;
    } else {
        return 1;        
    }

}

void displayResults() {
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (weights[i][j] != 0) cout << i << ' ' << j << ' ' << weights[i][j] << endl;
        }
    } 
}

int main() {
    cin >> n >> m >> L >> s >> t;
    int x, y, z;
    bool res;
    vector<tuple<int, int, ll>> in;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        in.emplace_back(x,y,z);
        edges[x].push_back({x, y, (z ? z : 1), 1, (z ? 0 : 1)});
        edges[y].push_back({y, x, (z ? z : 1), 1, (z ? 0 : 1)});
        weights[x][y] = (z ? z : 1);
        weights[y][x] = (z ? z : 1);
    }



    
    

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << weights[i][j] << ' ';
    //     }cout << endl;
    // }


    res = work();
    if (res) {
        displayResults();
        return 0;
    } 

    swap(s,t);
    for (int i = 0; i < n; i++) {
        edges[i].clear();
    }
    for (auto [x, y, z] : in) {
        edges[x].push_back({x, y, (z ? z : 1), 1, (z ? 0 : 1)});
        edges[y].push_back({y, x, (z ? z : 1), 1, (z ? 0 : 1)});
        weights[x][y] = (z ? z : 1);
        weights[y][x] = (z ? z : 1);
    }
    res = work();

    if (res) {
        displayResults();
        return 0;
    } 

    cout << "NO\n";
}