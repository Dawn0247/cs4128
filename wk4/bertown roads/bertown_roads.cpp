#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int, int>

const int N = 100005;
vector<int> edges[N];
vector<int> newEdges[N];
ll pred[N];
bool visited[N] = {0};
vector<pii> out;

int main() {
    // AAAAAAAAAAAAAAAAAAA
    int n, m, x, y, v;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    fill_n(&pred[0], N, -1);

    stack<int> s;
    for (int e : edges[1]) {
        s.push(e);
        pred[e] = 1;
    }
    visited[1] = true;

    // forward dfs
    while (!s.empty()) {
        v = s.top();
        s.pop();
        if (visited[v]) continue;
        visited[v] = true;
        newEdges[v].push_back(pred[v]);

        for (int e : edges[v]) {
            if (!visited[e]) {
                s.push(e);
                pred[e] = v;
            }
            else if (e != pred[v]) newEdges[e].push_back(v);
    
        }
    } 

    // reverse the dfs wtf
    fill_n(&visited[0], N, 0);
    s.push(1);

    while (!s.empty()) {
        v = s.top();
        s.pop();
        if (visited[v]) continue;
        visited[v] = true;
        for (int e : newEdges[v]) {
            if (!visited[e]) s.push(e);
        }
    }


    // check possible
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << 0 << '\n';
            return 0;
        }
    }

    // output
    for (int i = 1; i <= n; i++) {
        for (auto e : newEdges[i]) {
            cout << e << ' ' << i << '\n';
        }
    }
    
    
}

