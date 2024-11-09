#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define pll pair<ll, ll>
#define pii pair<int, int>
#define rep(i, n) for (int i = 0; i < n; i++)
#define repOne(i, n) for (int i = 1; i <= n; i++)
#define printArr(arr, n) rep(i, n) cout << arr[i] << ' '; cout << endl


const int N = 200005;
const int MAX_VERTICES = 200005;
vector<int> edges[N];
vector<int> newEdges[N];
bool seen[N];
int n;


// dist from start. -1 if unreachable.
int dist[N];
// previous node on a shortest path to the start
// Useful for reconstructing shortest paths
int prev[N];

bool bfs(int start) {
    fill(dist, dist+N, -1);
    dist[start] = 0;
    prev[start] = -1;

    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        if (newEdges[c].size() > 1) return false;
        for (int nxt : newEdges[c]) {
            // Push if we have not seen it already.
            if (dist[nxt] == -1) {
                dist[nxt] = dist[c] + 1;
                prev[nxt] = c;
                q.push(nxt);
            }
        }
    }
    return true;
}

// we will number the vertices in the order we see them in the DFS
int dfs_index[MAX_VERTICES];
// for each vertex, store the smallest number of any vertex we see
// in its DFS subtree
int lowlink[MAX_VERTICES];

// explicit stack
stack<int> s; // #include <stack>
bool in_stack[MAX_VERTICES];

// arbitrarily number the SCCs and remember which one things are in
int scc_counter;
int which_scc[MAX_VERTICES];

void connect(int v) {
  // a static variable doesn't get reset between function calls
  static int i = 1;
  // set the number for this vertex
  // the smallest numbered thing it can see so far is itself
  lowlink[v] = dfs_index[v] = i++;
  s.push(v);
  in_stack[v] = true;

  // continued

/*
 * tarjan 2
 */

  for (auto w : edges[v]) { // for each edge v -> w
    if (!dfs_index[w]) {  // w hasn't been visited yet
      connect(w);
      // if w can see something, v can too
      lowlink[v] = min(lowlink[v], lowlink[w]);
    }
    else if (in_stack[w]) {
      // w is already in the stack, but we can see it
      // this means v and w are in the same SCC
      lowlink[v] = min(lowlink[v], dfs_index[w]);
    }
  }
  // v is the root of an SCC
  if (lowlink[v] == dfs_index[v]) {
    ++scc_counter;
    int w;
    do {
      w = s.top(); s.pop();
      in_stack[w] = false;
      which_scc[w] = scc_counter;
    } while (w != v);
  }
}

// call connect for each vertex once


int main() {
    cin >> n;

    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        edges[i].push_back(x-1);
        edges[i].push_back(y-1);
    }

    for (int v = 0; v < n; ++v) if (!dfs_index[v]) connect(v);

    cout << scc_counter << endl;
    printArr(which_scc, n);
    

    for (int i = 0; i < n; i++) {
        for (int e : edges[i]) {
            if (which_scc[i] != which_scc[e]) {
                newEdges[which_scc[i]].push_back(which_scc[e]);
            }
        }
    }
    

    int start = which_scc[0];
    cout << bfs(start) << endl;

    for (int i = 1; i <= scc_counter; i++) {
        for (int e : newEdges[i]) {
            cout << i << ' ' << e << '\n';
        }
    }

    cout << "Yes\n";



}