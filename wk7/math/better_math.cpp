#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(var) cerr<< #var << " = " << var << endl
const int MAXN = 1000005;
vector<int> pf(MAXN + 1, 1);
map<int, int> f;

void sieve() {
    pf[0] = 0;
    for (int i = 2; i <= MAXN; i++) {
        if (pf[i] == 1) {
            for (int j = i; j <= MAXN; j+= i) {
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
    sieve();
    int p;
    cin >> p;
    primeFactorise(p);
    int maxExp = 0, minVal = 1, firstExp = f.begin()->second, cnt = 0;
    bool flag = false;
    for (auto [k, v] : f) {
        if (v > maxExp) maxExp = v;
        if (v != firstExp) flag = true;
        minVal *= k;
    }
    if (flag || __builtin_popcount(maxExp) != 1) cnt++;
    maxExp--;
    cnt += 32 - ((maxExp == 0) ? 32 : __builtin_clz(maxExp));
    cout << minVal << ' ' << ((p == 1) ? 0 : cnt)  << endl;
    
}
