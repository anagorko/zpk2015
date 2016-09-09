#ifndef WLASNA_H
#define WLASNA_H

#include "Gra.h"
#include <string>

using namespace std;

class Wlasna : public Gra
{
    int liczbaStanow;       // liczba stanow okreslona przez uzytkowanika, od nr 0 do liczbaStanow - 1
    int *stany;             // dynamiczna tablica mozliwych stanow

    int przejscia[MAX_SASIADOW + 1];     //tablica przejsc, indeks tablicy symbolizuje liczbe sasiadow, wartosc tablicy stan do ktorego przechodzimy

    // funkcja umozliwia wybor stanow i tylko do tych stanow mozna pzejsc
    void wczytajStany();

    // sprawdzenie czy tablica stany zawiera stan
    bool czyZawiera(int *stany, int ilosc, int stan) const;

    // zdefiniowanie do jakiego stanu przechodzimy w zaleznosci od liczby sasiadow
    void przypiszStany();

    // posortowanie wprowadzonych stanow w kolejnosci rosnacej;
    void sortujStany();

    // wybor stanu
    int wybierzStan(const string& komunikat);

public:
    Wlasna(int szerokosc, int wysokosc, int liczba_cykli);
    virtual ~Wlasna();
    void wykonajCykl();
    void losujPola();
    void rysuj();

};

#endif // WLASNA_H
