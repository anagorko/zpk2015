#include <iostream>

using namespace std;

int main()
{
    int liczbaPomiarow;
    cin>>liczbaPomiarow;

    int pomiary[liczbaPomiarow];
    for(int i=0; i<liczbaPomiarow; i++)
    {
        cin>>pomiary[i];
    }

    int liczbaZapytan;
    cin>>liczbaZapytan;
    int zapytania[liczbaZapytan];
    for(int i=0; i<liczbaZapytan; i++)
    {
        cin>>zapytania[i];
    }

    for(int i=0; i<liczbaZapytan; i++)
    {
        int poczatek = 0;
        int koniec = liczbaPomiarow - 1;
        while (poczatek < koniec)
        {
            int srodek = (poczatek + koniec) / 2;
            if (pomiary[srodek] >= zapytania[i])             // na œrodku jest element wiêkszy lub równy x...
                koniec = srodek;                  // zatem x jest w przedziale [poczatek, srodek]
            else                                  // wiemy, ¿e na œrodku jest element mniejszy od x...
                poczatek = srodek + 1;            // zatem x jest w przedziale [srodek+1, koniec]
        }
        if (pomiary[poczatek]!=zapytania[i])
        {
            cout<<0<<endl;
        }
        else
        {
            int pierwszeWystapienie = poczatek;
            poczatek = poczatek;
            koniec = liczbaPomiarow - 1;
            while (poczatek < koniec)
            {
                int srodek = (poczatek + koniec + 1) / 2;           // to jest dzielenie przez 2 z zaokr¹gleniem w górê
                if (pomiary[srodek] <= zapytania[i])
                    poczatek = srodek;
                else
                    koniec = srodek - 1;
            }
            cout<<poczatek-pierwszeWystapienie+1<<endl;
        }

    }

    return 0;
}
