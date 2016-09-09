#include<iostream>
using namespace std;

int wyszukaj(int szukana, int tablica[], int rozmiar)
{
    int pocz = 0;
    int kon = rozmiar - 1;
    int sr;

    while (pocz < kon)
    {
        sr = (pocz + kon) / 2;
        if (tablica[sr] >= szukana)
            kon = sr;
        else
            pocz = sr + 1;
    }
    return pocz;
}

int main()
{
    int n; //liczba czastek
    cin >> n;

    int v[n]; //tablica predkosci

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    int q;
    cin >> q; //liczba zapytan

    int zap[q];

    for (int i = 0; i < q; i++)
    {
        cin >> zap[i];
    }

    int poz; //pozycja szukanej liczby
    for (int i = 0; i < q; i++)
    {
        poz = wyszukaj(zap[i], v, n);
        if (v[poz] != zap[i])
        {
            cout << 0 << endl;
        } else
        {
            /*wyszukuje zap[i] + 1 i roznica pomiedzy
            jej pozycja a pozycja zap[i] jest liczba wystapien zap[i]*/
            cout << wyszukaj(zap[i] + 1, v, n) - poz << endl;
        }
    }
}
