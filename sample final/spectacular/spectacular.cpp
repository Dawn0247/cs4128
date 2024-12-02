#include <bits/stdc++.h>
#define ll long long
using namespace std;
// subtask 2 is ridculous for 1 mark
int main() {
    ll n;
    cin >> n;
    ll s = 0, m=1;
    for (char c : to_string(n)) {
        int i = c - '0';
        s += i;
        m *= i;
    }
    
    cout << (m*s == n ? "YES" : "NO");







}