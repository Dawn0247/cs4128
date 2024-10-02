// Discussed with Alperen Onur (z5161138)
#include <bits/stdc++.h>
#define ll long long 
#define pll pair<ll, ll>
#define pii pair<int, int>
#define tlll tuple<ll, ll, ll>

using namespace std;

ll n, m, s;

vector<ll> a, b, c;

// out array
vector<int> result;

// custom comparator, to sort multiset of tuples, by first then second element.
struct compare {
    bool operator()(const tlll &l, const tlll &r) const {
        return (get<0>(l) == get<0>(r)) ? get<1>(l) < get<1>(r) : get<0>(l) > get<0>(r);
    }
};

multiset<tlll, compare> students;
vector<pll> bugs;



bool solveInNumDays(int numDays) {
    multiset<pll> solvers;
    auto it = students.begin();
    ll cost = 0;
    for (int i = 0; i < m; i++) {
        auto bug = bugs[i];
        // cout << bug.first << ' ' << bug.second << '\n';

        while (it != students.end() && get<0>(*it) >= bug.first) {
            solvers.insert(make_pair(get<1>(*it), get<2>(*it)));
            it++;
        }

        if (solvers.empty()) return false;

        auto solver = solvers.begin();

        // cout << "SOLVER: " << (*solver).first << ' ' << (*solver).second << '\n';

        for (int k = 0; k < numDays && i < m; k++, i++) {
            result[bugs[i].second] = (*solver).second;
        } i--;

        cost += (*solver).first;
        solvers.erase(solver);

        
    }
    // cout << "DAYS: " << numDays << " COST: " << cost << " s: " << s << endl;
    return cost <= s;
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    ll in;
    cin >> n >> m >> s;

    // data reading
    
    
    for (int i = 0; i < m; i++) {
        cin >> in;
        a.push_back(in);
        result.push_back(-1);
    }

    for (int i = 0; i < n; i++) {
        cin >> in;
        b.push_back(in);
    }

    for (int i = 0; i < n; i++) {
        cin >> in;
        c.push_back(in);
    }

    // construct data structure

    // students is a multiset of tuples: each term contains (b[index], c[index], index)
    // sorted in ability descending and ties broken with cost ascending
    for (int i = 0; i < n; i++) {
        students.insert(make_tuple(b[i], c[i], i));
    }

    // bugs is a vector of pairs: each term contains (a[index], index)
    // sorted in complexity descending
    for (int i = 0; i < m; i++) {
        bugs.push_back(make_pair(a[i], i));
    } sort(bugs.rbegin(), bugs.rend());


    // print data for debug
    // for (auto bug : bugs) {
    //     cout << "Index: " << bug.second << " Complexity: " << bug.first << '\n';
    // }

    // for (auto it = students.begin(); it != students.end(); it++) {
    //     cout << "Index: " << get<2>(*it) << " Ability: " << get<0>(*it) << " Cost: " << get<1>(*it) << '\n';
    // }


    int l = 1, r = m+1;
    while (l < r) {
        int mid = (l+r)/2;
        // cout << "B SEARCH: " << l << ' ' << mid << ' ' << r << '\n';
        if (solveInNumDays(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
        
    }

    if (l == m + 1) {
        cout << "NO\n";
        return 0;
    }
    // cout << "NUM DAYS: " << l << endl;
    solveInNumDays(l);

    cout << "YES\n";
    for (int i : result) {
        cout << i + 1 <<  ' ';
    } cout << '\n';
} 