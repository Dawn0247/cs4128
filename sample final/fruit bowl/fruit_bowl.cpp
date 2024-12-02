#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct fruit {
    int e, h;

    bool operator<(const fruit& o) const {
        return (e == o.e) ? h > o.h : e > o.e;
    }
};

const int MAXN = 200005;
vector<fruit> f;
priority_queue<int> eatable;
int main() {
    int n, x, y, days = 0; 
    cin >> n;
    for (int  i = 0; i < n; i++) {
        cin >> x >> y;
        f.push_back({x,y});
        if (x > days) days = x;
    } sort(f.begin(), f.end());

    int id = 0;
    ll h = 0;
    while (days--) {
        while (f[id].e > days) {
            eatable.push(f[id].h);
            // cout << "PUSHED: " << f[id].h << endl;
            id++;
        }
        // cout << "DAYS: " << days << endl;
        if (!eatable.empty()) {
            h += eatable.top();
            eatable.pop();   
        }
    }


    cout << h << endl;
}