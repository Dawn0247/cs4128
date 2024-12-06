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

int n, m;

vector<int> fillPos(vector<int> board, int pos, int colour) {
  if (pos < 0 || pos >= m || board[pos] == colour) return board;
  else {
    board[pos] = colour;
    board = fillPos(board, pos+1, colour);
    board = fillPos(board, pos-1,colour);
  }

  return board;

}

int boardDifference(vector<int> target, vector<int> board) {
  int res = 0;
  for (int i = 0; i < m; i++) {
    if (target[i] != board[i]) res++;
  }
  return res;
}

int main() {
  cin >> n >> m;
  vector<int> target;
  vector<int> board;
  char c;
  for (int i = 0; i< m; i++) {
    char
  }



}
