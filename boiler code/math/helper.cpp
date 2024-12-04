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
const ll MOD = 1e9 + 7;

ll modAddition(ll x, ll y, ll m) { 
    return (x % m + y % m) % m;
}

ll modSubtraction(ll x, ll y, ll m) {
    return (((x - y) % m) + m ) % m; 
}

ll modMultiplication(ll x, ll y, ll m) {
    return (x % m * y % m) % m;
}

ll modPower(ll x, ll y, ll m) {
    ll r = 1;
    x = x % m;
    while (y > 0) {
        if (y % 2 == 1) {
            r = (r * x) % m;
        }
        y = y >> 1;
        x = (x * x) % m;
    }
    return r;
}

ll modInverse(ll x, ll m) {
    return modPower(x, m-2, m);
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll f[MAXN];
void nCrPreComp(int m) {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++)
    f[i] = (i * f[i-1]) % m;
}

ll nCr(int n, int r, int m) {
    ll res = (f[n] * modInverse(f[n-r], m)) % m;
    res = (res * modInverse(f[r], m)) % m;
    return res;
}   
int main() {
    cout << modPower(10, 10, 1e9+7) << endl;
    cout << modInverse(10000000000  , 100000007) << endl; 
    nCrPreComp(MOD);
    cout << nCr(100, 50, MOD);
}