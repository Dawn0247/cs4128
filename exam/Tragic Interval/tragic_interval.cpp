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

const int MAXN = 1e5 + 5;
const ll INF = 1e18;
int n, m;
vector<ll> nums;

int checkTragic(int l, int r) {
  ll mnm = INF, mxm = 0;
  for (int i = l ; i <= r; i++) {
    mnm = min(mnm, nums[i]);
    mxm = max(mxm, nums[i]);
  }

  for ( int i = 0; i < l; i++) {
    if (nums[i] >= mnm && nums[i] <= mxm) return false;
  }

  for ( int i = r+1; i < n; i++) {
    if (nums[i] >= mnm && nums[i] <= mxm) return false;
  }
  return true;
}

int main() {
  cin >> n >> m;
  ll x, y;
  for (int i = 0; i < n; i++) {
    cin >> x;
    nums.push_back(x);
  }
  // cout << checkTragic(2, 3);
  char cmd;
  for (int i = 0; i < m; i++) {
    cin >> cmd >> x >> y;
    x--; y--;
    if (cmd == 'C') {
      cout << (checkTragic(x, y) ? "YES" : "NO") << endl;
    } else {
      swap(nums[x], nums[y]);
    }

  }

}
