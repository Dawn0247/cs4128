#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int, int>

const int N = 5005;
const int M = 5005;
vector<pii> edges[N];
int out[N];
int state[N] = {0}; // 0: unvisited, 1: visiting, 2: visited
bool f = false;

void dfs(int v) {
    state[v] = 1;
    for (auto [to, id] : edges[v]) {
        if (state[to] == 0) dfs(to);
        else if (state[to] == 1) {
            out[id] = 2;
            f = true;
        } 
    }
    state[v] = 2;
}

int main() {
    int n, m, x, y;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        edges[x].push_back(make_pair(y, i));
        out[i] = 1;
    }   

    for (int i = 1; i <= n; ++i) {
        if (state[i] == 0) dfs(i);
    }

    cout << (f ? 2 : 1) << endl;
    for (int i = 0; i < m; i++) {
        cout << out[i] << ' ';
    } cout << '\n';
}