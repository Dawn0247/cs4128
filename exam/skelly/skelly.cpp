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
int n, m;
const int MAXN = 2e5+5;
vector<int> edges[MAXN];
int dist[MAXN];
int pred[MAXN];
bool seen[MAXN];



int dfs(int start, int a, int b) {
    fill(seen, seen+MAXN, 0);
    stack<int> s;
    s.push(start);
    int cnt = 0;

    while (!s.empty()) {
        int c = s.top(); s.pop();
        cnt++;
        if (!seen[c]) seen[c] = true;

        for (int nxt : edges[c]) {
            if (!seen[nxt]) {
              if ((c==a) && (nxt == b) || (c == b && nxt == a)) {

                continue;
              }
              s.push(nxt);
            }
        }
    }
    return cnt;
}

int main() {
  cin >> n >> m;
  int x, y;
  vector<pii> edgeList;
  for (int i = 0; i < m; i++ ) {
    cin >> x >> y;
    edges[x].push_back(y);
    edges[y].push_back(x);
    edgeList.push_back({x,y});
  }


  vector<int> cnts;
  for (auto [a,b] : edgeList) {
    int reached = dfs(a, a, b);
    cnts.push_back(reached * (n-reached));
  }

  int mxm = 0;
  for (auto i : cnts) mxm = max(mxm, i);
  cout << mxm;





}
