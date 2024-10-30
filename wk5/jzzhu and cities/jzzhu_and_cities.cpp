#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define t3l tuple<ll, ll, ll>
#define pll pair<ll, ll>

const int N = 100005;
const ll INF = 1e18;
vector<t3l> edges[N];
bool visited[N] = {0};
ll dist[N];
pll pred[N];
int n, m, k;

struct compare {
    bool operator()(const t3l &l, const t3l &r) const {
        return (get<0>(l) == get<0>(r)) ? get<2>(l) > get<2>(r) : get<0>(l) > get<0>(r);
    }
};

priority_queue<t3l, vector<t3l>, compare> pq;

void dijkstra(int s) {
    pq.emplace(0, s, 0);
    while (!pq.empty()) {
        auto [d, v, i] = pq.top();
        pq.pop();

        if (visited[v]) continue;
        if (i > m) k--;
        dist[v] = d;
        visited[v] = true;

        for (auto [weight, u, id] : edges[v]) {
            if (!visited[u]) pq.emplace(weight + d, u , id);
        }   
    }
}

int main() {
    cin >> n >> m >> k;
    int x, y, z;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        edges[x].emplace_back(z, y, i);
        edges[y].emplace_back(z, x, i);
    }

    for (int i = 1; i <= k; i++) {
        cin >> y >> z;
        edges[1].emplace_back(z, y, m + i);
        edges[y].emplace_back(z, 1, m + i);
    }
    dijkstra(1);

    cout << k << '\n';
}