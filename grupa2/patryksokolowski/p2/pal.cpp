#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;


int main() {
    string s;
    cin >> s;
    int l = s.length();
    bool x = false;
    for (int i=0;i<l;i++) {
        if (s[i]!=s[l-1-i]){
            cout << "NIE";
            return 0;
        }
    }
    cout << "TAK";
}
