#include "Amoeba.h"
#include <iostream>

using namespace std;

Amoeba::Amoeba(int szerokosc, int wysokosc, int liczba_cykli):
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}


Amoeba::~Amoeba() { }

void Amoeba::wykonajCykl()
{
    zamienMacierze();

    int ilosd_sasiadow;
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            ilosd_sasiadow = zliczZywychSasiadow(w, k);
            if(matrix_prev[w][k] > 0)
            {
                switch(ilosd_sasiadow)
                {
                case 1: case 3: case 5: case 8:
                    matrix[w][k] = 1;
                    break;
                default:
                    matrix[w][k] = 0;
                }
            }
            else
            {
                switch(ilosd_sasiadow)
                {
                case 3: case 5: case 7:
                    matrix[w][k] = 1;
                    break;
                default:
                    matrix[w][k] = 0;
                }
            }
        }
    }
    ++liczba_wykonanych_cykli;
}


void Amoeba::losujPola()
{
    losuj(1);
}
