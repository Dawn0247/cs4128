#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(var) cerr<< #var << " = " << var << endl
const int MAXN = 500005;
const int MAXA = 1e7;
vector<int> pf(MAXA + 1, 1);
set<int> f;
int out1[MAXN], out2[MAXN];

void sieve() {
    pf[0] = 0;
    for (int i = 2; i <= MAXA; i++) {
        if (pf[i] == 1) {
            for (int j = i; j <= MAXA; j+= i) {
                if (pf[j] == 1) pf[j] = i;
            }
        }
    }
}

void primeFactorise(int x) {
    f.clear();
    while (x != 1) {
        f.insert(pf[x]);
        x = x / pf[x];
    }
}

int main() {
    sieve();
    fill(out1, out1+MAXN, 1);
    fill(out2, out2+MAXN, 1);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        primeFactorise(p);
        if (f.size() <= 1) {
            out1[i] = -1;
            out2[i] = -1;
            continue;
        }

        auto it = f.begin();
        out1[i] = *it;
        it++;
        for (it; it != f.end(); it++) {
            out2[i] *= *it;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << out1[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << out2[i] << ' ';
    }
}
