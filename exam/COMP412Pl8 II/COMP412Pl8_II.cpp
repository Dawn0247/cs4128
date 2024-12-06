#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll,ll>
#define repRange(x,y,i) for (int i = x; i < y; i++)
#define printArr(n, arr) repRange(0, n, i) { cerr << arr[i] << ' '; } cerr << endl
#define print2DArr(n, m, arr) repRange(0, n, j) { printArr(m, arr[j]); }
#define printPairArr(n, arr) repRange(0, n, i) { cerr << arr[i].first << ' ' << arr[i].second << '\n'; };
#define debug(var) cerr << #var << ": " <<  var << endl
#define flag(i) cerr << "Flag: " << i

using namespace std;
vector<int> plates;
const int MAXN = 1e6 + 5;


int main() {
  int n,x;
  bool jT = true;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x;
    plates.push_back(x);
  }
  int js=0, ts=0;
  for (auto p : plates) {
    if (!p) continue;
    if (jT) js++;
    else ts++;
    jT = !jT;
  }

  cout << js << ' ' << ts << endl;


}
