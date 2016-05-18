#include <iostream>

using namespace std;


long ileliczb(long t[], long pyt,int n)
{
    long poczatek = 0;
    long koniec = n - 1;
    long lewy;
    long prawy;
    long srodek;

//Szukam potencjalnie pierwszej wystepujacej wartosci, czyli przesuwam sie w tablicy maksymalnie w lewo, dlatego >=
    while (poczatek < koniec)
{
    srodek = (poczatek + koniec) / 2;
    if (t[srodek] >= pyt)
        koniec = srodek;
    else
        poczatek = srodek + 1;
}
//Sprawdzam czy liczba wystepuje, jezeli nie to juz zwracam odpowiedz 0
    if(t[poczatek]== pyt)
        lewy= poczatek;
    else
        return 0;

//Teraz szukam ostatniego wystapienia liczby, przesuwam sie w tablicy w prawo, dlatego >
poczatek = 0;
koniec = n - 1;

    while (poczatek < koniec)
{
    srodek = (poczatek + koniec) / 2;
    if (t[srodek] > pyt)
        koniec = srodek;
    else
        poczatek = srodek+1;
}
//Sprawdzam gdzie liczba wystepuje, bo juz musi
    if (t[poczatek]==pyt)
        prawy=poczatek;
    else prawy = poczatek-1;

//Patrze na roznice miedzy prawym i lewym i zwracam wartosc

return prawy-lewy+1;
}




int main()
{
    int n;
    cin >> n;
    long t[n];
    int lzap;
    for(int i=0;i<n;i++){
    cin>>t[i];
    }
    cin>>lzap;
    long pyt[lzap];

    for(int i=0;i<lzap;i++){
       cin >> pyt[i];
    }

    for(int i=0; i<lzap;i++){
        cout << ileliczb(t,pyt[i],n)<<endl;
    }
}
