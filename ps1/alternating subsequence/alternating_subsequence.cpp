#include <iostream>

using namespace std;

int main() {
    int testCases;
    cin >> testCases;
    for (int i = 0; i < testCases; i++) {
        int numTerms;
        cin >> numTerms;
        long long runningMax;
        bool isNeg;
        long long runningSum = 0;
        long long next;

        for (int j = 0; j < numTerms; j++) {
            cin >> next;
            if (j == 0) {
                isNeg = next < 0;
                runningMax = next;
            }

            if ( (next < 0) == isNeg) {
                runningMax = max(runningMax, next);
            } else {
                runningSum += runningMax;
                isNeg = next < 0;
                runningMax = next;
            }
        }

        cout << runningSum + runningMax << '\n';



    }
    return 0;
} 