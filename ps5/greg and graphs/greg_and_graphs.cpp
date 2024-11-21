#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define t3l tuple<ll, ll, ll>
#define pll pair<ll, ll>

const int N = 1005;
const ll INF = 1e18;
ll adj[N][N];
ll dist[N][N];
vector<ll> out;
int rm[N];
int n;

int main() {
    cin >> n;
    fill_n(&dist[0][0], N*N, INF);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
            dist[i][j] = adj[i][j];
        } 
    }

    for (int i = 0; i < n; i++) {
        cin >> rm[i];
    }

    reverse(rm, rm + n);
    for (int id = 0; id < n; id++) {
        int i = rm[id];
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }

        ll sum = 0;
        for (int rowIdx = 0; rowIdx <= id; rowIdx++) {
            int row = rm[rowIdx];
            for (int colIdx = 0; colIdx <= id; colIdx++) {
                int col = rm[colIdx];
                sum += dist[row][col];
            }
        }
        out.push_back(sum);
    }

    reverse(out.begin(), out.end());
    for (auto i : out) {
        cout << i << ' ';
    } cout << '\n';


    


}
