#include<iostream>
using namespace std;

int main()
{
int n, liczba;
cin >> n;
int tablica[n];
for (int i=0; i<n; i++)
{
    cin >> tablica[i];
}
cin >> liczba;
int t[liczba];
for (int i=0;i<liczba;i++)
{
    cin >> t[i];
}
//--------------------------------------------------------------
for (int i=0;i<liczba;i++)
{
int licznik, srodek, pierwsza, ostatnia;
int x = t[i];
int poczatek = 0;
int koniec = n - 1;
while (poczatek < koniec)
{
    srodek = (poczatek + koniec+1) / 2;
    if (tablica[srodek] <= x)
        poczatek = srodek;
    else
        koniec = srodek - 1;
}
if (tablica[poczatek]==x)
{
    ostatnia = poczatek;
    poczatek = 0;
while (poczatek < koniec)
{
    srodek = (poczatek + koniec) / 2;
    if (tablica[srodek] >= x)
        koniec = srodek;
    else
        poczatek = srodek + 1;
}
    pierwsza = poczatek;
    licznik = ostatnia - pierwsza +1;
}
else licznik = 0;
cout << licznik<< endl;
}
return 0;
}
