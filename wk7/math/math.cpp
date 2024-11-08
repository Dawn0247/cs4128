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
    int curr, cnt = 0;
    cin >> curr;
    int prev = curr;
    sieve();
    while (prev != (curr = work(curr))) {
        cout << prev << ' ' << curr << '\n';
        cnt += (prev == curr * curr) ? 1 : 2;
        prev = curr;
    }

    cout << curr << ' ' << cnt << endl;
    
}
