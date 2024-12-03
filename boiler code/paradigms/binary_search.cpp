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
int arr[10] = {0,1,2,3,4,5,6,7,8,9};


// Search left if func is true
int leftBSearch(int l, int r, function <bool(int)> f) {
    while (l < r) {
        int m = (l+r)/2;
        if (f(m)) r = m;
        else l = m + 1;
    }
    return l;
}

// Search right if func is true
int rightBSearch(int l, int r, function <bool(int)> f) {
    while (l < r) {
        int m = (l+r)/2;
        if (f(m)) l = m + 1;
        else r = m;   
    }
    return l;
}


// Search right if func is true
double floatRBSearch(double l, double r, function<bool(double)> f) {
    for (int it = 0; it < 70; it ++) {
        double m = (l + r) / 2;
        if (f(m)) l = m;
        else r = m;
    }

    return l;
}

// Search right if func is true
double floatLBSearch(double l, double r, function<bool(double)> f) {
    for (int it = 0; it < 70; it ++) {
        double m = (l + r) / 2;
        if (f(m)) r = m;
        else l = m;
    }
    return l;
}

bool greaterThan5(int i) {
    return arr[i] > 5;
}

bool lessThan5(int i) {
    return arr[i] < 5;
}

bool sqGreaterThan2(double x) {
    return x*x > 2;
}

bool sqLessThan2(double x) {
    return x*x < 2;
}

int main() {
    int o = leftBSearch(0, 9, greaterThan5);
    cout << o << endl;

    o = rightBSearch(0, 9, lessThan5);
    cout << o << endl;

    double r = floatLBSearch(0, 100, sqGreaterThan2);
    cout << r << endl;


    r = floatRBSearch(0, 100, sqLessThan2);
    cout << r << endl;

}