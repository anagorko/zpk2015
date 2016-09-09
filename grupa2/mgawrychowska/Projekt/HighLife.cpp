#include "HighLife.h"
#include <iostream>

using namespace std;

HighLife::HighLife(int szerokosc, int wysokosc, int liczba_cykli):
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}

HighLife::~HighLife() { }


void HighLife::wykonajCykl()
{
    zamienMacierze();



    int ilosc_sasiadow;
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            ilosc_sasiadow = zliczZywychSasiadow(w, k);
            switch(ilosc_sasiadow)
            {
                case 2:
                    break;
                case 3:
                     matrix[w][k] = 1;
                     break;
                case 6:
                     matrix[w][k] = 1 - matrix_prev[w][k];
                     break;
                default:
                     matrix[w][k] = 0;
            }
        }
    }
}


void HighLife::losujPola()
{
    losuj(1);
}
