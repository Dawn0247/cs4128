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
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const ll INF = 1e18;

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

void print_path(int destination) {
    if (dist[destination] == INF) {
        cout << "No path to node " << destination << "\n";
        return;
    }
    vector<int> path;
    for (int at = destination; at != -1; at = pred[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << "\n";
}

int main() {
    int n, m; // Number of nodes and edges
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w}); // If the graph is undirected
    }

    int source;
    cin >> source;

    dijkstra(source);

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            cout << "Node " << i << ": unreachable" << endl;
        } else {
            cout << "Node " << i << ": " << dist[i] << "\n";
            cout << "Path: ";
            print_path(i);
        }
    }

    return 0;
}
