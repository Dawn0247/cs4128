#include <iostream>
#include <string>   
#include <cmath>
#include <algorithm>

using namespace std;

long long getTriangleNum(long long x) {
    x = 8*x + 1;
    long long rt = sqrt(x);
    if (rt * rt != x) {
        return -1;
    } 

    return ((rt - 1) / 2) + 1;
    

}

int main() {
    long long count00, count01, count10, count11;
    cin >> count00;
    cin >> count01;
    cin >> count10;
    cin >> count11;

    count00 = getTriangleNum(count00);
    count11 = getTriangleNum(count11);


    if (count00 + count10 + count01 == 1) {
        count00 = 0;
    } else if (count11 + count10 + count01 == 1) {
        count11 = 0;
    }    

    if (count00 == -1 || count11 == -1) {
        cout << "impossible\n";
        return 0;|
    }

    if (count01 + count10 != count00 * count11) {
        cout << "impossible\n";
        return 0;
    }
    
  
    string out = string(count00, '0');

    long long workingCount = max(count10, count01);
    
    long long numInsert = (count00 == 0) ? count11 : workingCount/count00;
    out.insert(count00, numInsert, '1');

    long long remaining = count11 - numInsert;
    long long lastPos = workingCount - (numInsert * count00);

    if (remaining > 0) {
        out.insert(lastPos, 1, '1');
        out.insert(0, max( (long long) 0 ,remaining - 1), '1');
    }
    
    if (count10 > count01) {
        reverse(out.begin(), out.end());
    }
    cout << out << '\n';
    
    return 0;

} 