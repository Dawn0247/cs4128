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

vector<int> edges[MAXN];
int dist[MAXN];
int pred[MAXN];
bool seen[MAXN];

void bfs(int start) {
    fill(dist, dist+MAXN, -1);
    dist[start] = 0;
    pred[start] = -1;

    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (int nxt : edges[c]) {
            // Push if we have not seen it already.
            if (dist[nxt] == -1) {
                dist[nxt] = dist[c] + 1;
                pred[nxt] = c;
                q.push(nxt);
            }
        }
    }
}

void dfs(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int c = s.top(); s.pop();
        if (!seen[c]) seen[c] = true;

        for (int nxt : edges[c]) {
            if (!seen[nxt]) s.push(nxt);
        }
    }
}

int main() {

    return 0;
}