#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define ll long long 
#define vll vector<ll>
const ll REM = 1e9+7;
int N, M, K;

int main() {
    cin >> M;
    M++;
    ll a, b, c, tmp;
    a = 1;
    b = 1;
    for (int i = 3; i <= M; i++) {
        c = (i - 1) * b + (i-2) * a;
        c = c % REM;
        a = b;
        b = c;
    }
    cout << b << endl;
}
