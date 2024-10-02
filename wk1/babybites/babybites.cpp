#include <iostream>
#include <string>


using namespace std;

int main() {
    int numVals;
    cin >> numVals;
    string next;
    int num = 1;
    for (int i = 0; i < numVals; i++) {
        
        cin >> next;
        if (next != "mumble" && stoi(next) != num) {
            cout << "something is fishy";
            return 0;
        }
        num++;
    }
    
    cout << "makes sense";
    return 0;
} 