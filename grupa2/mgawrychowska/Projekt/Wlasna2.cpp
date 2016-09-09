#include "Wlasna2.h"
#include "wczytywanie.h"
#include "Przejscie.h"
#include <fstream>


Wlasna2::Wlasna2(int szerokosc, int wysokosc, int liczba_cykli) :
Gra(szerokosc, wysokosc, liczba_cykli), liczbaStanow(1), przejscia(NULL)
{
    if(wczytajWartosc(1, 2, "1 - wczytanie istniejacych przejsc z pliku\n2 - zdefiniowanie nowych przejsc\nOpcja:") == 1)
    {
        if(!wczytajPrzejsciaZpliku())
        {
            definiujStany();
        }
        else
        {
            definiujPrzejscia();
            int pytanie = wczytajWartosc(1, 2, "Czy zapisac reguly do pliku?\n1 - TAK\n2 - NIE: ");
            if(pytanie == 1)
                zapiszDoPliku();
        }
    }
    else
        definiujStany();


    losujPola();
}

Wlasna2::~Wlasna2()
{
    delete [] przejscia;
}

string Wlasna2::pobierzNazwePliku(const string& komunikat)
{
    string nazwaPliku;
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
        cin >> nazwaPliku;

        cin.ignore( numeric_limits<streamsize>::max(), '\n');
        // testowanie nazwy pliku
        break;

    }
    return nazwaPliku;
}


void Wlasna2::wykonajCykl()
{
    zamienMacierze();
    int ilosc_sasiadow;
    int stan;
    int rodzajSasiedztwa;

    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            stan = matrix_prev[w][k];
            rodzajSasiedztwa = przejscia[stan].zliczanyRodzaj();
            if(rodzajSasiedztwa >= 0)
                ilosc_sasiadow = zliczSasiadowWstanie(w, k, stan);
            else
                ilosc_sasiadow = zliczZywychSasiadow(w, k);

            matrix[w][k] = przejscia[stan].pobierzNowyStan(ilosc_sasiadow);
        }
    }
}

void Wlasna2::losujPola()
{
    losuj(liczbaStanow - 1);
}

void Wlasna2::rysuj()
{
    rysuj2();
}

void Wlasna2::definiujStany()
{
    liczbaStanow = wczytajWartosc(2, 20, "Okresl liczbe stanow komorek z przedzialu [2; 20]:");
    przejscia = new Przejscie [liczbaStanow];

    cout << "Domyslnie komorki planszy nie przechodza do innych stanow\n"
    << "Nalezy okreslic do jakiego stanu przechodzi komorka, dla jakiego rodzaju sasiedztwa" << endl;

    for(int nr_stanu = 0; nr_stanu < liczbaStanow; ++nr_stanu)
        przejscia[nr_stanu].ustalStany(nr_stanu, liczbaStanow);

    definiujPrzejscia();

    int pytanie = wczytajWartosc(1, 2, "Czy zapisac reguly do pliku?\n1 - TAK\n2 - NIE: ");
    if(pytanie == 1)
    {
        zapiszDoPliku();
    }
}

void Wlasna2::zapiszDoPliku()
{
    while(true)
    {
        string nazwaPliku = pobierzNazwePliku("Podaj nazwe pliku do zapisu:");
        ofstream out;
        out.open(nazwaPliku.c_str());
        if(!out.is_open())
        {
            cout << "Nie mozna otworzyc pliku do zapisu" << endl;
            if(wczytajWartosc(1, 2, "Czy zapisac reguly do innego pliku?\n1 - TAK\n2 - NIE: ") == 1)
                continue;
            else
                break;
        }
        else    // otwarto
        {
            out << "liczba stanow: " << liczbaStanow << endl;
            for(int nr_stanu = 0; nr_stanu < liczbaStanow; ++nr_stanu)
                przejscia[nr_stanu].wypisz(out);

            out.close();
            break;
        }
    }
}

// funkcja umozliwia dodanie przejscia do innego stanu lub zmiane sposobu zliczania sasiadow, dla wybranego stanu
void Wlasna2::definiujPrzejscia()
{
    char komunikat[100];     // tablica przechowuje komunikat wyjsciowy
    sprintf(komunikat, "Wybierz stan, dla ktorego definiujemy przejscia [0; %d] lub -1 gdy koniec:", this->liczbaStanow - 1);

    int wybranyStan;
    while(true)
    {
        wybranyStan = wczytajWartosc(-1, this->liczbaStanow - 1, string(komunikat));
        if(wybranyStan == -1)
            break;

        przejscia[wybranyStan].modyfikuj();
        wypiszPrzejscia();
    }



}


bool Wlasna2::wczytajPrzejsciaZpliku()
{
    while(true)
    {
        string nazwaPliku = pobierzNazwePliku("Podaj nazwe pliku do odczytu:");
        ifstream in;
        in.open(nazwaPliku.c_str());
        if(!in.is_open())
        {
            cout << "Nie mozna otworzyc pliku z regulami" << endl;
            if(wczytajWartosc(1, 2, "Czy odczytac reguly z innego pliku?\n1 - TAK\n2 - NIE: ") == 1)
                continue;
            else
                return false;
        }
        else    // otwarto
        {
            in.ignore( numeric_limits<streamsize>::max(), ':');
            if(!(in >> liczbaStanow))
            {
                cout << "Problem z odczytem pliku" << endl;
                in.close();
                return false;
            }

            //cout << "liczba: " << liczbaStanow << endl;

            in.ignore( numeric_limits<streamsize>::max(), '\n');

            przejscia = new Przejscie [liczbaStanow];

            for(int nr_stanu = 0; nr_stanu < liczbaStanow; ++nr_stanu)
            {
                if(!przejscia[nr_stanu].wczytaj(in, nr_stanu, liczbaStanow))
                {
                    cout << "Problem z odczytem pliku" << endl;
                    in.close();
                    delete [] przejscia;
                    return false;
                }
            }
            in.close();
            break;
        }
    }

    cout << "liczba stanow: " << liczbaStanow << endl;
    wypiszPrzejscia();

    return true;
}

void Wlasna2::wypiszPrzejscia()
{
    //nr_stanu - stan poczatkowy
    Przejscie::wypiszNaglowek();
    for(int nr_stanu = 0; nr_stanu < liczbaStanow; ++nr_stanu)
        przejscia[nr_stanu].wypiszRekordy();
    cout << endl;
}
