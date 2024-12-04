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

const ll INF = 1e18;
const ll MOD = 1e9 + 7;

int n, m;
vector<int> pf;
map<int, int> f;


void sieve(int n) {
    pf.resize(n+1); fill(pf.begin(), pf.end(), 1);
    pf[0] = 0;
    for (int i = 2; i <= n; i++) {
        if (pf[i] == 1) {
            for (int j = i; j <= n; j+= i) {
                if (pf[j] == 1) pf[j] = i;
            }
        }
    }
}

void primeFactorise(int x) {
    while (x != 1) {
        if (f.find(pf[x]) != f.end()) f[pf[x]]++;
        else f[pf[x]] = 1;
        x = x / pf[x];
    }
}

int main() {
    int p = 180180;
    sieve(2e6);
    primeFactorise(p);
    for (auto [k,v] : f) {
        cout << k << ": " << v << endl;
    }
    
}
