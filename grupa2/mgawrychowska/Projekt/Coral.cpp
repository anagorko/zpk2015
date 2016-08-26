#include "Coral.h"
#include <iostream>

using namespace std;

Coral::Coral(int szerokosc, int wysokosc, int liczba_cykli):
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}

Coral::~Coral() { }

void Coral::wykonajCykl()
{
    zamienMacierze();



    int ilosd_sasiadow;
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            ilosd_sasiadow = zliczZywychSasiadow(w, k);
            switch(ilosd_sasiadow)
            {
                case 4: case 5: case 6: case 7: case 8:
                    matrix[w][k] = matrix_prev[w][k];
                    break;
                case 3:
                    matrix[w][k] = 1;
                default:
                    matrix[w][k] = 0;
            }
        }
    }
}


void Coral::losujPola()
{
    losuj(1);
}

