#ifndef WCZYTYWANIE_H
#define WCZYTYWANIE_H

#include <iostream>
#include <limits>                   // numeric_limits<streamsize>::max()

using namespace std;


// Pomocniczy szablon funkcji do kontrolowanego wprowadzania danych.
// min_val - minimalna dopuszczalna wartosc
// max_val - maksymalna dopuszczalna wartosc
template <typename T>
T wczytajWartosc(T min_val, T max_val, const string& komunikat)
{
    T wartosc;
    while(true)
    {
        cout << komunikat;

        // pominiecie bialych znakow do znaku enter lub do znaku alfanumerycznego
        while(cin.peek() != '\n' && isspace(cin.peek()))
        {
            cin.get();
        }

        // wprowadzono sam enter ponownie idziemy do wprowadzania wartosci
        if(cin.peek() == '\n')
        {
            cin.get();
            continue;
        }
        cin >> wartosc;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
        {
            cin.ignore( numeric_limits<streamsize>::max(), '\n');
            if(wartosc >= min_val && wartosc <= max_val)
                break;

        }
    }
    return wartosc;
}


#endif // WCZYTYWANIE_H
