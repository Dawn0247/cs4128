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
bool inQueue[MAXN];

void spfa(int source, int n) {
    // Initialize distances and inQueue flags
    fill(dist, dist + n + 1, INF);
    fill(inQueue, inQueue + n + 1, false);
    fill(pred, pred + n + 1, -1);

    queue<int> q;
    dist[source] = 0;
    q.push(source);
    inQueue[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        // Relax all edges from the current node
        for (const Edge &edge : adj[u]) {
            int v = edge.v;
            long long weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;

                // If node v is not in the queue, add it
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
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
    int n, m;
    cin >> n >> m; // Number of nodes and edges

    for (int i = 0; i < m; i++) {
        int u, v;
        long long weight;
        cin >> u >> v >> weight;
        adj[u].push_back({u, v, weight});
        // If the graph is undirected, add the reverse edge as well
        // adj[v].push_back({v, u, weight});
    }

    int source;
    cin >> source; // Source node for SPFA

    spfa(source, n);

    // Output shortest distances from source to all nodes
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
