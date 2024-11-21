#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 1e9 + 7;
int t;

int m_pow(ll x, ll n, int m) {
    if (n == 0) return 1;
    ll a = m_pow(x, n/2, m);
    a = a * a % m;
    if (n%2 == 1) a = a * x % m;
    return a;
}

int main() {
    int n;
    ll toSub, currDiff;
    
    cin >> t;
    while (t--) {
        cin >> n;
        vector<ll> arr(n);
        for(int i  = 0; i < n; i++) {
            cin >> arr[i];
        } 
        sort(arr.begin(), arr.end());

        currDiff = 0, toSub = 0;
        for (int i = 1; i <= n-1; i++) {
            toSub = (2 * toSub + arr[i-1]) % MOD;
            currDiff = currDiff + (m_pow(2, i, MOD) - 1) * arr[i] - toSub;
            currDiff %= MOD;
        }
        cout << (currDiff) << endl;;
        
    }
}