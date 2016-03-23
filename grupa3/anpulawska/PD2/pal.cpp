#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    bool palindrom = true;
    
    for (int i = 0; i < s.size(); i++)
        if (s[i] != s[s.size() - 1 - i]){
            palindrom = false;
            break;
            }
    
    if (palindrom)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
