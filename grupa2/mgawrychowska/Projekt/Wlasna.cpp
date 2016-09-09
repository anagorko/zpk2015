#include "Wlasna.h"
#include <iostream>
#include <cstdlib>

#include "wczytywanie.h"



Wlasna::Wlasna(int szerokosc, int wysokosc, int liczba_cykli) :
Gra(szerokosc, wysokosc, liczba_cykli)
{
    liczbaStanow = wczytajWartosc(2, 8, "Podaj liczbe stanow z przedzialu [2, 8]:");
    stany = new int [liczbaStanow];
    wczytajStany();
    sortujStany();
    przypiszStany();

    losujPola();
}

Wlasna::~Wlasna()
{
    delete [] stany;
}

void Wlasna::wykonajCykl()
{
    zamienMacierze();
    int ilosc_sasiadow;
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            ilosc_sasiadow = zliczZywychSasiadow(w, k);
            matrix[w][k] = przejscia[ilosc_sasiadow];
        }
    }

}

void Wlasna::losujPola()
{
    for(int w = 0; w < wysokosc; ++w)
        for(int k = 0; k < szerokosc; ++k)
            matrix_prev[w][k] = matrix[w][k] = stany[rand() % (liczbaStanow)];
}

void Wlasna::wczytajStany()
{
    char liczba[10];                    // tablica przechowuje liczbe w postaci znakowej
    cout << "Nalezy wprowadzic numery stanow dla " << liczbaStanow << " stanow" << endl;
    for(int nr = 0; nr < liczbaStanow; )
    {
        itoa(nr + 1, liczba, 10);                       //zamiana typu int na lancuch w tabkicy liczba
        stany[nr] = wczytajWartosc(0, 100, "Podaj wartosc dla stanu " + string(liczba) + " z przedzialu [0; 100]:");
        if(!czyZawiera(stany, nr, stany[nr]))
            ++nr;
        else
            cout << "Powtorzony numer stanu" << endl;
    }

}

bool Wlasna::czyZawiera(int *stany, int ilosc, int stan) const
{
    for(int i = 0; i < ilosc; ++i)
    {
        if(stany[i] == stan)
            return true;
    }
    return false;
}

void Wlasna::przypiszStany()
{
    char liczba[10];                    // tablica przechowuje liczbe w postaci znakowej

    cout << "Mozliwe stany: ";
    for(int i = 0; i < liczbaStanow; ++i)
        cout << stany[i] << " ";
    cout << endl;
    for(int n_sasiadow = 0; n_sasiadow <= MAX_SASIADOW; ++n_sasiadow)
    {
        itoa(n_sasiadow, liczba, 10);
        przejscia[n_sasiadow] = wybierzStan("Majac " + string(liczba) + " sasiadow przechodzimy do stanu:");
    }
}

void Wlasna::sortujStany()
{
    int temp;
    for(int i = liczbaStanow - 1; i > 0; --i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(stany[j] > stany[j + 1])
            {
                temp = stany[j];
                stany[j] = stany[j + 1];
                stany[j + 1] = temp;
            }
        }
    }
}

void Wlasna::rysuj()
{
    rysuj2();
}

int Wlasna::wybierzStan(const string& komunikat)
{
    int wartosc;
    while(true)
    {
        cout << komunikat;

        // pominiecie bialych znakow do znaku enter lub do znaku alfanumerycznego
        while(cin.peek() != '\n' && isspace(cin.peek()))
        {
            cin.get();
        }

        // wprowadzono sam enter ponownie idziemy do wprowadzania wartosci
        if(cin.peek() == '\n')
        {
            cin.get();
            continue;
        }
        cin >> wartosc;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
        {
            cin.ignore( numeric_limits<streamsize>::max(), '\n');
            if(czyZawiera(stany, liczbaStanow, wartosc))
                break;

        }
    }
    return wartosc;
}
