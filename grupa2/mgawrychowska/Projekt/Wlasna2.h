#ifndef WLASNA2_H
#define WLASNA2_H

#include "Gra.h"
#include <string>

using namespace std;

class Przejscie;

class Wlasna2 : public Gra
{
    int liczbaStanow;                   // stany sa okreslone w numerach od 0 do liczbaStanow-1
    Przejscie *przejscia;               // tablica przejsc w zaleznosci od numeru stanu

    // funkcja umozliwia definiowanie przejsc do okreslonych stanow w zaleznosci od liczby sasiadow
    void definiujStany();
    void definiujPrzejscia();
    // funkcja umozliwia wczytanie przejsc zdefiniowanych wczesniej.
    bool wczytajPrzejsciaZpliku();

    string pobierzNazwePliku(const string& komunikat);

    void zapiszDoPliku();


public:
    Wlasna2(int szerokosc, int wysokosc, int liczba_cykli);
    virtual ~Wlasna2();

    void wykonajCykl();
    void losujPola();
    void rysuj();
    void wypiszPrzejscia();


};

#endif // WLASNA2_H
