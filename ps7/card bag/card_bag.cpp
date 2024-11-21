#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 998244353;
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
    cout << m_pow(10, MOD-2, MOD);


}