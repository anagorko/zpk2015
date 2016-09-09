#include "Amazing.h"
#include <iostream>

using namespace std;

Amazing::Amazing(int szerokosc, int wysokosc, int liczba_cykli):
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}

Amazing::~Amazing() { }


void Amazing::wykonajCykl()
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
                case 1: case 2: case 3: case 4: case 5:
                    matrix[w][k] = 2;
                    break;
                default:
                    matrix[w][k] = 0;
                }
            }
            else
            {
                switch(ilosd_sasiadow)
                {
                case 3:
                    matrix[w][k] = 1;
                    break;
                default:
                    matrix[w][k] = 0;

                }
            }
        }

    }
}


void Amazing::losujPola()
{
    losuj(2);
}
