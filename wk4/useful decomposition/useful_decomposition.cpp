#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int N = 100005;
const ll INF = 1e18;
ll conn[N];
vector<ll> out;

int main() {
    ll n, x, y, src, cnt = 0;
    bool f = false;
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        cin >> x >> y;
        conn[x]++;
        conn[y]++;
    }

    for (int i = 1; i <= n; i++) {
        // find common vertex if exists
        if (conn[i] > 2) {
            if (!f) {
                f = true;
                src = i;
            // too many
            } else {
                cout << "No\n";
                return 0;
            }
        // end point of traversal
        } else if (conn[i] == 1) {
            out.push_back(i);
            cnt++;
        }
    }

    cout << "Yes\n";
    if (f) {
        cout << cnt << endl;
        for (ll i: out) {
            cout << src << ' ' << i << '\n';
        }
    } else {
        cout << 1 << '\n' << out[0] << ' ' << out[1] << '\n';
    }
}

