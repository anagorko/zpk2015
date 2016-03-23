#include <iostream>
using namespace std;

int main()
    {
    string slowo;
    string wynik = "TAK";


    getline(cin, slowo);

    for (int i=0; i < slowo.length() /2 ;i++)
    {
        if (slowo[i] != slowo[slowo.length()-i-1])
            wynik = "NIE";
    }

    cout << wynik << endl;
}
