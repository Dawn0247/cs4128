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
int n, m;

int dfs_index[MAXN];
int lowlink[MAXN];

stack<int> s;
bool in_stack[MAXN];

int scc_counter;
int which_scc[MAXN];

void connect(int v) {
	static int i = 1;
	lowlink[v] = dfs_index[v] = i++;
	s.push(v);
	in_stack[v] = true;

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

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
    }

    for (int v = 0; v < n; ++v) {
        if (!dfs_index[v]) connect(v);
    }

    // Output the SCCs
    cout << "Node to SCC mapping:" << endl;
    for (int v = 0; v < n; ++v) {
        cout << "Node " << v << " is in SCC " << which_scc[v] << endl;
    }

    return 0;
}
