#include <iostream>
using namespace std;

int main()
{
    int n;
    int wynik;

    cin >> n;

    if (n == 0)
        wynik = 1;
    else if (n % 4 == 1)
        wynik = 2;
    else if (n % 4 == 2)
        wynik = 4;
    else if (n % 4 == 3)
        wynik = 8;
    else if (n % 4 == 0)
        wynik = 6;

    cout << wynik << endl;
}
