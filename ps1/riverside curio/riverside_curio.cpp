#include <bits/stdc++.h>

using namespace std;

int main() {
    long long numTerms;
    cin >> numTerms;
    vector<long long> above;

    for (int i = 0; i < numTerms; i++) {
        long long next;
        cin >> next;
        above.push_back(next);
    }

    vector<long long> placed;
    
    long long prev = 0;
    for (long long i: above) {
        long long next = max(prev, i + 1);
        placed.push_back(next);
        prev = next;
    }
    
    reverse(placed.begin(), placed.end());
    prev = placed[0];
    for(int i = 1; i < numTerms; i++) {
        if (prev - placed[i] > 1) {
            placed[i] = prev - 1;
        }

        prev = placed[i];
    }
    reverse(placed.begin(), placed.end());

    long long runningSum = 0;
    for (int i = 0; i < numTerms; i++) {
        runningSum += placed[i] - above[i] - 1;
    }

    cout << runningSum << '\n';
} 