#include <iostream>
#include <string>
using namespace std;

int main() {
    string slowo;
    cin >> slowo;
    bool warunek = true;
    int j = slowo.length() - 1;
    for (int i = 0; i <= j; i++) {
        warunek = warunek && (slowo[i] == slowo[j]);
        j--;
    }
    if (warunek)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
