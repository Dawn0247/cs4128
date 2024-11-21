#include <bits/stdc++.h>

using namespace std;



void displayVector(vector<long long> v) {
    for (long long i : v) {
        cout << i << ' ';
    } cout << '\n';
}



int main() {
    int length;
    cin >> length;
    vector<long long> arr(length);
    vector<int> id(length);
    vector<pair<int, int>> swaps;

    for (int i = 0; i<length; i++) {
        int next;
        cin >> next;
        arr[i] = next;
        id[i] = i+1;
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swaps.push_back({id[j], id[j+1]});
                swap(arr[j], arr[j+1]);
                swap(id[j], id[j+1]);
            }
        }
    }

    cout << swaps.size() << '\n';
    reverse(swaps.begin(), swaps.end());
    for (pair<int, int> p : swaps) {
        printf("%d %d\n", p.first, p.second);
    }


} 

