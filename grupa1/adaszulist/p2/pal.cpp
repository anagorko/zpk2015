#include <iostream>
#include <string>
using namespace std;

int main(){
    string slowo;
    cin >> slowo;
    bool palindrom = true;

    for (int i = 0; i < slowo.length() / 2; i++) {
        if (slowo [i] != slowo[slowo.length() - 1 - i])
            palindrom = false;}

    if (palindrom == true)
        cout << "TAK";
    else
        cout << "NIE" << endl;
    return 0;
}
