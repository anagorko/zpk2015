#ifndef GRA_H
#define GRA_H


class Gra
{
    //enum stan {zywy = 0, martwy = 1};

    // sprawdzenie, czy pole o zadanych wspolrzednych miesci sie w planszy
    bool poprawnaWspolrzedna(int wiersz, int kolumna) const {return wiersz >= 0 && kolumna >= 0 && wiersz < wysokosc && kolumna < szerokosc; }

protected:
    int szerokosc;
    int wysokosc;
    int liczba_wykonanych_cykli;        // liczba cykli ktora byla wykonana
    int **matrix;                       // aktualna macierz
    int **matrix_prev;                  // poprzednia macierz

    int zliczZywychSasiadow(int wiersz, int kolomna) const;
    int zliczSasiadowWstanie(int wiersz, int kolomna, int stan) const;
    void zamienMacierze();

    // wylosowanie wartosci poczatkowych dla macierzy
    void losuj(int max_val);



public:
    Gra(int szerokosc, int wysokosc, int liczba_cykli = 0);
    int iloscWykonanychCykli() { return liczba_wykonanych_cykli; }
    virtual ~Gra();
    virtual void wykonajCykl() = 0;
    virtual void losujPola() = 0;
    void rysuj();
    void print();


    struct Kolor
    {
        unsigned char r, g, b;
    };
    const static Kolor kolory[4];
    const static int rozmiarPola;

};

#endif // GRA_H
