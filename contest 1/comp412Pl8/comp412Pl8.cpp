#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define ll long long 
#define vll vector<ll>
const long long INF = 1e18;
const int MAXN = 2e5+5;
int N, M, K;
ll arr[MAXN];

int main() {
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + M, greater<ll>());

    vll out;
    ll mnm = arr[0];

    for (int i = 0; i < M; i++) {
        if (mnm - i > 0) {
            out.push_back(arr[i]);
            if (i + arr[i] < mnm) {
                mnm = i + arr[i];
            }
        }
    }
    
    cout << out.size() << endl;
    for (ll i : out) {
        cout << i <<  ' ';

    } cout << endl;

}
