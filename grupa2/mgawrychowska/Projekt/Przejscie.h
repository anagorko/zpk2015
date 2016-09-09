#ifndef PRZEJSCIE_H
#define PRZEJSCIE_H

//tablicaPrzejsc[numer
#include "Gra.h"
#include <iostream>
#include <fstream>

using namespace std;


class Przejscie
{
    int liczbaStanow;                       // liczba mozliwych stanow numerowana od 0
    int stanObecny;                         // stan z ktorego przechodzimy
    int zliczanyRodzajSasiada;              // 0 - zliczanie sasiadow 0, itd, -1 - zliczanie zywych sasiadow

    int tablicaPrzejsc[MAX_SASIADOW + 1];   // indeks tablicy to liczba sasiadow, a wartosc tablicy to stan docelowy
public:
    Przejscie();
    virtual ~Przejscie();
    void ustalStany(int nr_stanu, int liczbaStanow);                        // wypisanie przejsc na konsole
    int zliczanyRodzaj() const { return zliczanyRodzajSasiada; }

    // funkcja zapisuje stany do strumienia out
    void wypisz(ostream& out) const;
    bool wczytaj(ifstream& in, int nr_stanu, int liczbaStanow);                                         // wczytanie z pliku

    int pobierzNowyStan(int liczbSasiadow) const { return tablicaPrzejsc[liczbSasiadow]; }
    void wypiszPrzejscia() const;

    // dodawanie przejsc
    void dodajPrzejscia();

    // zmiana sposobu zliczania sasiadow
    void zmienSposobZliczaniaSasiadow();

    // zmiana sposobu zliczania sasiadow lub dodawanie przejscia
    void modyfikuj();

    // wypisanie samych rekordow
    void wypiszRekordy() const;

    static void wypiszNaglowek();

    static string nameStart;
    static string nameKoniec;
    static string liczbaSasiadow;

};

#endif // PRZEJSCIE_H
