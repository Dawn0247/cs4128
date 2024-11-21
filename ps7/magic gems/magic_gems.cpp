#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, x) for (int i = 0; i < x; i++)
#define flag(x) printf("DEBUG: %d", x)
#define print2d(x, n, m) rep(i, n) { rep(j, m) cout << x[i][j] << ' '; cout << endl; }
#define modmul(a,b,m) ((a%m)*(b%m))%m

const int MOD = 1000000007;
ll n, m;

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
	cin >> n >> m;
	Matrix rec(m);
	rec.v[0][0] = 1;
	rec.v[0][m-1] = 1;

	for (int i = 1; i < m; i++)
    	rec.v[i][i-1] = 1;

	rec = rec^n;
	
	cout << rec.v[0][0] % MOD << endl;


}