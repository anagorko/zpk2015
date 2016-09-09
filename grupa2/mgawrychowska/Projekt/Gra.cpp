#include "Gra.h"
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>

using namespace std;

const Gra::Kolor Gra::kolory[4] = {{0,0,0}, {255,255,0},{255,0,255}, {127, 127, 255}};
const int Gra::rozmiarPola = 10;



Gra::Gra(int szer, int wys, int liczba_cyk)
    :szerokosc(szer), wysokosc(wys), liczba_cykli(liczba_cyk)
{
    matrix = new int * [wysokosc];
    matrix_prev = new int * [wysokosc];
    for(int i = 0; i < wysokosc; ++i)
    {
        matrix[i] = new int [szerokosc];
        matrix_prev[i] = new int [szerokosc];
    }
}

Gra::~Gra()
{
    for(int i = 0; i < wysokosc; ++i)
    {
        delete [] matrix[i];
        delete [] matrix_prev[i];
    }
    delete [] matrix;
    delete [] matrix_prev;
}

int Gra::zliczZywychSasiadow(int wiersz, int kolumna) const
{
    int ilosc = 0;
    if(poprawnaWspolrzedna(wiersz - 1, kolumna - 1) && matrix_prev[wiersz - 1][kolumna - 1] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz - 1, kolumna + 1) && matrix_prev[wiersz - 1][kolumna + 1] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz + 1, kolumna + 1) && matrix_prev[wiersz + 1][kolumna + 1] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz + 1, kolumna - 1) && matrix_prev[wiersz + 1][kolumna - 1] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz, kolumna - 1) && matrix_prev[wiersz][kolumna - 1] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz, kolumna + 1) && matrix_prev[wiersz][kolumna + 1] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz - 1, kolumna) && matrix_prev[wiersz - 1][kolumna] > 0)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz + 1, kolumna) && matrix_prev[wiersz + 1][kolumna] > 0)
        ++ilosc;

    return ilosc;
}


int Gra::zliczSasiadowWstanie(int wiersz, int kolumna, int stan) const
{
    int ilosc = 0;
    if(poprawnaWspolrzedna(wiersz - 1, kolumna - 1) && matrix_prev[wiersz - 1][kolumna - 1] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz - 1, kolumna + 1) && matrix_prev[wiersz - 1][kolumna + 1] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz + 1, kolumna + 1) && matrix_prev[wiersz + 1][kolumna + 1] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz + 1, kolumna - 1) && matrix_prev[wiersz + 1][kolumna - 1] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz, kolumna - 1) && matrix_prev[wiersz][kolumna - 1] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz, kolumna + 1) && matrix_prev[wiersz][kolumna + 1] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz - 1, kolumna) && matrix_prev[wiersz - 1][kolumna] == stan)
        ++ilosc;
    if(poprawnaWspolrzedna(wiersz + 1, kolumna) && matrix_prev[wiersz + 1][kolumna] == stan)
        ++ilosc;

    return ilosc;
}
void Gra::rysuj()
{
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            al_draw_filled_rectangle(k * rozmiarPola, w * rozmiarPola,(k + 1)* rozmiarPola, (w + 1)* rozmiarPola, al_map_rgb(kolory[matrix[w][k]].r,
                                                                                                                                 kolory[matrix[w][k]].g,
                                                                                                                                 kolory[matrix[w][k]].b));
        }
    }
    al_flip_display();
}

void Gra::rysuj2()
{
    unsigned char r, g, b;
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            r = (matrix[w][k] * 20) % 256;
            g = (matrix[w][k] * 50) % 256;
            b = 255 / (matrix[w][k] % 4 + 1);
            al_draw_filled_rectangle(k * rozmiarPola, w * rozmiarPola,(k + 1)* rozmiarPola, (w + 1)* rozmiarPola, al_map_rgb(r, g, b));
        }
    }
    al_flip_display();
}

void Gra::print()
{
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
           cout << matrix[w][k] << " ";
        }
        cout << endl;
    }
    al_flip_display();
}

void Gra::losuj(int max_val)
{
    for(int w = 0; w < wysokosc; ++w)
        for(int k = 0; k < szerokosc; ++k)
            matrix_prev[w][k] = matrix[w][k] = rand() % (max_val + 1);
}


void Gra::zamienMacierze()
{
    int **tmp = matrix;
    matrix = matrix_prev;
    matrix_prev = tmp;
}



