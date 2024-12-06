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

const int MAXN = 1e5 + 5;
const ll INF = 1e18;
int n, m, src, dst;

struct Edge {
    int u, v;
    ll weight;
    bool operator>(const Edge &other) const {
        return weight > other.weight;
    }
};

vector<Edge> adj[MAXN];
ll dist[MAXN];
bool visited[MAXN];
int pred[MAXN];

void dijkstra(int source) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    fill(dist, dist + MAXN, INF);
    fill(visited, visited + MAXN, false);
    fill(pred, pred + MAXN, -1);

    dist[source] = 0;
    pq.push({-1, source, 0});

    while (!pq.empty()) {
        int u = pq.top().v;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (auto &[_, v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u; // Update predecessor
                pq.push({u, v, dist[v]});
            }
        }
    }
}

int main() {
    cin >> n >> m >> src >> dst;
    int a, b;
    for (int bus = 0; bus < m; bus++) {
      cin >> a >> b;
      // cout << a << b << endl;
      for (int i = 2*a; i <= n; i+=a) {
        adj[i-a].push_back({i-a, i, b});
        adj[i].push_back({i, i-a, b});
      }
    }

    dijkstra(src);
    cout << ((dist[dst] == INF) ? 0 : dist[dst]);

}
