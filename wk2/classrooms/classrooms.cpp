#include <bits/stdc++.h>
#define ll long long 
#define pll pair<ll, ll>
#define pii pair<int, int>

using namespace std;

int main() {
    ll n, k;
    cin >> n >> k;
    vector<pll> act(n);

    for (int i = 0; i < n; i++) {
        cin >> act[i].second >> act[i].first;
    }

    sort(act.begin(), act.end());
    
    ll ans = 0;
    multiset<ll> m;

    for (int i = 0; i < k; i++) m.insert(0);


    for (int i = 0; i < n; i++) {
        auto ind = m.upper_bound(act[i].second);

        if (ind == m.begin()) continue; 

        ans++;
        ind--;
        m.erase(ind);
        m.insert(act[i].first+1);

    }
    

    cout << ans << '\n';
} 