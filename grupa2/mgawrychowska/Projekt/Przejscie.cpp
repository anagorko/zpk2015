#include "Przejscie.h"
#include "wczytywanie.h"
#include <cstdio>
#include <string>
#include <iomanip>

string Przejscie::nameStart = "Stan poczatkowy";
string Przejscie::nameKoniec = "Stan docelowy";
string Przejscie::liczbaSasiadow = "Liczba sasiadow";

Przejscie::Przejscie(): stanObecny(-1) { }


Przejscie::~Przejscie() { }

// ustalenie numeru stanu dla przejscia, oraz liczbe miozliwych stanow
void Przejscie::ustalStany(int nr_stanu, int liczbaStanow)
{
    this->liczbaStanow = liczbaStanow;
    stanObecny = nr_stanu;                  //stan startowy

        // na poczatek definiujemy przejscia na samego siebie
    for(int l_sasiadow = 0; l_sasiadow < MAX_SASIADOW + 1; ++l_sasiadow)
        tablicaPrzejsc[l_sasiadow] = stanObecny;

    zmienSposobZliczaniaSasiadow();

}

// dodawanie przejsc
void Przejscie::dodajPrzejscia()
{
    char komunikat[100];
    sprintf(komunikat, "Podaj stan docelowy z przedzialu [0; %d]:",liczbaStanow - 1);
    const string komunikatStanDocelowy(komunikat);
    while(true)
    {
        if(wczytajWartosc(1, 2, "Dodac kolejne przejscie?\n1 - TAK\n2 - NIE: ") == 2)
            break;

        int stanDocelowy = wczytajWartosc(0, liczbaStanow - 1, komunikatStanDocelowy);

        sprintf(komunikat, "Dla jakiej liczby sasiadow przechodzimy do stanu %d [0; 8]?:", stanDocelowy);

        int liczbaSasiadow = wczytajWartosc(0, MAX_SASIADOW, string(komunikat));

        tablicaPrzejsc[liczbaSasiadow] = stanDocelowy;
    }
}

void Przejscie::zmienSposobZliczaniaSasiadow()
{
    char komunikat[100];                    // tablica przechowuje liczbe w postaci znakowej
    sprintf(komunikat, "Jakiego rodzaju sasiada mamy zliczac bedac w stanie %d? [0; %d] lub -1 gdy niezerowych:", this->stanObecny, this->liczbaStanow - 1);
    zliczanyRodzajSasiada = wczytajWartosc(-1, liczbaStanow - 1, string(komunikat));
}

void Przejscie::modyfikuj()
{
    char komunikat[200];
    sprintf(komunikat, "Modyfikacja przejsc lub sposobu zliczania sasiadow dla stanu %d\n0 - koniec modyfikacji\n1 - zmiana sposobu zliczania sasiadow\n2 - zmiana przejsc\nopcja:", stanObecny);
    int wybor;
    while(true)
    {

        wybor = wczytajWartosc(0, 2, string(komunikat));
        if(wybor == 0)
            break;
        if(wybor == 1)
            zmienSposobZliczaniaSasiadow();
        else
        {
            wypiszPrzejscia();
            dodajPrzejscia();
        }
    }
}

void Przejscie::wypisz(ostream& out) const
{
    out << "Rodzaj sasiedztwa:" << zliczanyRodzajSasiada << endl;
    for(int l_sasiadow = 0; l_sasiadow < MAX_SASIADOW + 1; ++l_sasiadow)
        out << l_sasiadow << '\t' << tablicaPrzejsc[l_sasiadow] << endl;
}

// in - strumien wejsciowy z otwartego juz wczesniej pliku
// funkcja zwraca false w przypadku nieoczekiwanego niepowodzenia czytania ustalonych danych
bool Przejscie::wczytaj(ifstream& in, int nr_stanu, int liczbaStanow)
{
    this->liczbaStanow = liczbaStanow;
    stanObecny = nr_stanu;

    in.ignore( numeric_limits<streamsize>::max(), ':');
    in >> zliczanyRodzajSasiada;
    if(in.fail())
        return false;

    in.ignore( numeric_limits<streamsize>::max(), '\n');

    for(int l_sasiadow = 0; l_sasiadow <= MAX_SASIADOW; ++l_sasiadow)
    {
        in.ignore( numeric_limits<streamsize>::max(), '\t');
        in >> tablicaPrzejsc[l_sasiadow];
        if(in.fail())
            return false;
        in.ignore( numeric_limits<streamsize>::max(), '\n');
    }
    return true;
}

void Przejscie::wypiszPrzejscia() const
{
    cout << "Stan biezacy: " << stanObecny << endl;
    cout << "Zliczany rodzaj sasiedztwa: ";
    if(zliczanyRodzajSasiada == -1)
        cout << "niezerowy" << endl;
    else
        cout << zliczanyRodzajSasiada << endl;

    wypiszNaglowek();
    wypiszRekordy();

    cout << endl;
}

void Przejscie::wypiszRekordy() const
{
    for(int l_sasiadow = 0; l_sasiadow <= MAX_SASIADOW; ++l_sasiadow)
    {
        if(tablicaPrzejsc[l_sasiadow] != stanObecny)
            cout << setw(nameStart.size()) << stanObecny << '\t'
            << setw(nameKoniec.size()) << tablicaPrzejsc[l_sasiadow] << '\t'
            << setw(liczbaSasiadow.size()) << l_sasiadow << endl;
    }
}

void Przejscie::wypiszNaglowek()
{
    cout << nameStart << '\t' << nameKoniec << '\t' << liczbaSasiadow << endl;
}
