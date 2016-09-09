#include "Artist.h"
#include <iostream>

using namespace std;

Artist::Artist(int szerokosc, int wysokosc, int liczba_cykli) :
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}

Artist::~Artist() { }


void Artist::wykonajCykl()
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
                case 0: case 1: case 2: case 4: case 5: case 6: case 7: case 8:
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
                case 3: case 4:
                    matrix[w][k] = 1;
                    break;
                default:
                    matrix[w][k] = 0;
                }
            }
        }
    }
}


void Artist::losujPola()
{
    losuj(1);
}
