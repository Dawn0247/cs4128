#include <bits/stdc++.h>
#define ll long long 
#define pll pair<ll, ll>
#define pii pair<int, int>

using namespace std;

int main() {
    string s;
    cin >> s;
    vector<int> pos[26];
    vector<int> ord;
    vector<char> t;
    vector<char> out;
    
    int i = 0;
    for (char c : s) {
        pos[(int)c - 97].push_back(i);
        i++;
    }

    for (vector<int> v : pos) {
        for (int i : v) {
            ord.push_back(i);
        } 
    }


    int j = 0;

    for (auto it = ord.begin(); it != ord.end(); it++) {
        while (!t.empty() && t.back() <= s[*it]) {
            out.push_back(t.back());
            t.pop_back();
        }
            
        while (j < *it) {
            t.push_back(s[j]);
            j++;
        }

        if (*it >= j) {
            out.push_back(s[*it]);
            j++;
        }

        if (*it == s.size() - 1) {

            for (char c : out) {
                cout << c;
            } 

            reverse(t.begin(), t.end());
            for (char c : t) {
                cout << c;
            } cout << '\n';
            break;   
        } 
        
    }
} 