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

const ll INF = 1e18;
const ll MOD = 1e9 + 7;

int n, m;

ll modmul(ll x, ll y, ll m) {
    return ((x % m) * (y % m)) % m;
}


struct Matrix {
	int n;
	vector<vector<ll>> v;

	Matrix(int _n) : n(_n) {
		v.resize(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				v[i].push_back(0);
	}

	Matrix operator*(const Matrix &o) const {
		Matrix res(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					res.v[i][j] += modmul(v[i][k], o.v[k][j], MOD); 
		return res;
	}

	static Matrix getIdentity(int n) {
		Matrix res(n);
		for (int i = 0; i < n; i++)
			res.v[i][i] = 1;
		return res;
	}
	
	Matrix operator^(ll k) const {
		Matrix res = Matrix::getIdentity(n);
		Matrix a = *this;
		while (k) { // building up in powers of two
			if (k&1) res = res*a;
			a = a*a;
			k /= 2;
		}
		return res;
	}
};


int main() {



}