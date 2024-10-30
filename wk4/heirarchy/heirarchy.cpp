#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int N = 1005;
const ll INF = 1e18;
ll arr[N];

int main() {
    ll n, m, x, y, z;
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        arr[i] = INF;
        cin >> x;
    }
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        arr[y] = min(arr[y], z);
    }

    ll out = 0, c = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i] == INF) c++;
        else out += arr[i];
    }

    printf("%lld\n", (c >= 2) ? -1 : out);

}

