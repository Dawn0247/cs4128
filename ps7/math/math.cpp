#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1000005;
vector<int> pf(MAXN + 1, 1);

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

int work(int x) {
    int out = -1, prev = -1, next = 1;
    bool f = 1; // are the prev 2 numbers we see different
    while (prev != 1) {
        next = pf[x];
        if (f) out *= prev;
        if (next != prev) f = 1;
        else f = !f;
        x = x / next;
        prev = next;
    }
    return out;
}

int main() {
    sieve();
    int p, cnt = 0;
    cin >> p;

    // sqrt until not perfect square, add 1 per step
    int c = sqrt(p);
    while (c != 1 && c*c == p) {
        p = c;
        c = sqrt(c);
        cnt++;
    }

    // work the first step
    c = work(p);
    if (c != p) cnt += 2;  
    p = c;

    while (p != (c = work(c))) {
        cnt++;
        p = c;
    }

    cout << c << ' ' << cnt << endl;
    
}
