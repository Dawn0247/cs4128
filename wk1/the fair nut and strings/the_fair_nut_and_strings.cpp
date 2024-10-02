#include <iostream>
#include <string>   
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

long long indexNonZero(vector<long long> v) {
    long long i = 0;
    for (long long e: v) {
        if (e != 0) 
            return i;
        i++;
    }

    return 10e6;
}

void cascade(vector<long long>& self, vector<long long>& other, long long index, long long n, long long change) {
    self[index] -= change;
    index++;
    while (index < n) {
        other[index] += change;
        index++;
     }
}
void displayVector(vector<long long> v) {
    for (long long i: v) {
        cout << i << ' ';
    } cout << '\n';
}
int main() {
    long long n, k;
    cin >> n;
    cin >> k;
    string s, t;
    cin >> s;
    cin >> t;

    if (s == t) {
        cout << n << '\n';
        return 0;
    }
    vector<long long> left;
    vector<long long> right;
    long long runningSum = 0;
    
    long long i;
    for (i = 0; i < n; i++) {
        if (s[i] != t[i]) {
            break;
        }
    }

    s = s.substr(i, n-i);
    t = t.substr(i, n-i);
    n -= i;
    long long constPref = i;

    

    for (char c : s) 
        right.push_back( (c == 'a') ? 1 : 0 );
    runningSum += n;

    if (k == 1) {
        cout << runningSum + constPref << '\n';
        return 0;
    }

    for (char c : t) 
        left.push_back( (c == 'b') ? 1 : 0 ); 
    runningSum += n;

    left[0] = 0;
    right[0] = 0;

    i = 2;
    while (i < k) {
        bool lzeros = all_of(left.begin(), left.end(), [](long long j) { return j == 0;});
        bool rzeros = all_of(right.begin(), right.end(), [](long long j) { return j == 0;});

        if (lzeros && rzeros) {
            break;
        }

        long long lIndex = indexNonZero(left);
        long long rIndex = indexNonZero(right);

        
        long long change;
        if (lIndex <= rIndex) {
            change = min(k-i, left[lIndex]);
            cascade(left, right, lIndex, n, change);
        } else {
            change = min(k-i, right[rIndex]);
            cascade(right, left, rIndex, n, change);
        }
        i += change;
        runningSum += change*(n - min(lIndex, rIndex));
        
    }

    runningSum += constPref;
    cout << runningSum  << '\n';

} 