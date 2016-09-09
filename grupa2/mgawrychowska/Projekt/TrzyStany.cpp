#include "TrzyStany.h"
#include <iostream>

using namespace std;


TrzyStany::TrzyStany(int szerokosc, int wysokosc, int liczba_cykli):
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}


TrzyStany::~TrzyStany() { }

void TrzyStany::wykonajCykl()
{
    zamienMacierze();

    int ilosd_sasiadow;
    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            ilosd_sasiadow = zliczZywychSasiadow(w, k);
            if(matrix_prev[w][k] == 0 && ilosd_sasiadow == 3)
                matrix[w][k] = 2;
            else if(matrix_prev[w][k] > 0 && (ilosd_sasiadow == 2 || ilosd_sasiadow == 3))
                matrix[w][k] = 1;
            else
                matrix[w][k] = 0;
        }
    }
}


void TrzyStany::losujPola()
{
   losuj(2);
}
