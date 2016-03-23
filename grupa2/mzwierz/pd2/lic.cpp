#include <iostream>
using namespace std;

int main()
{
    int n;
    string liczba;

    cin >> n;

    int i=2;
    for (int i=2; i * i <= n; i++ )
    {
        if (n % i == 0)
            liczba = "zlozona";
    }
    if (liczba!="zlozona")
        liczba="pierwsza";
    cout <<liczba<< endl;
}
