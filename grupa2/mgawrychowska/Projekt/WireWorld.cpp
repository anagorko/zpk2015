#include "WireWorld.h"
#include <iostream>

using namespace std;

WireWorld::WireWorld(int szerokosc, int wysokosc, int liczba_cykli) :
Gra(szerokosc, wysokosc, liczba_cykli)
{
    losujPola();
}

WireWorld::~WireWorld() { }

void WireWorld::wykonajCykl()
{
    zamienMacierze();

    for(int w = 0; w < wysokosc; ++w)
    {
        for(int k = 0; k < szerokosc; ++k)
        {
            switch(matrix_prev[w][k])
            {
            case 0:
                matrix[w][k] = 0;
                break;
            case 1:
                matrix[w][k] = 2;
                break;
            case 2:
                matrix[w][k] = 3;
                break;
            case 3:
                switch(zliczSasiadowWstanie(w, k, 1))
                {
                case 1: case 2:
                    matrix[w][k] = 1;
                    break;
                default:
                    matrix[w][k] = 3;
                    break;
                }
            }
        }
    }
    ++liczba_wykonanych_cykli;
}

void WireWorld::losujPola()
{
    losuj(3);
}
