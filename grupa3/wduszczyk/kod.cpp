#include <iostream>
#include <string>

using namespace std;

int main() {
        char a, b;
    int kod, wynik;
    cin >> a >> b;
    kod = b;
    if (kod >= 48 && kod <= 57)
        {wynik = (a - 48) * 16 + kod - 48;}
    else
        {wynik = (a - 48) * 16 + kod - 55;}
    cout << wynik << endl;
    cout << (char)wynik << endl;
    }