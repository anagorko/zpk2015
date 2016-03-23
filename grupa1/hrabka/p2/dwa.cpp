#include <iostream>

using namespace std;

int policz(int pierwszy[], int drugi[], int liczba)
{
    int suma = 0;
    for(int i=0; i<liczba; i++)
    {
        if(pierwszy[i] < drugi[i])
        {
            suma += pierwszy[i];
        }
        else
        {
            suma += drugi[i];
        }
    }
    return suma;
}

int main()
{
    int nSklepow, nProduktow;

    cin >> nSklepow >> nProduktow;

    int ceny[nSklepow][nProduktow];

    int temp;

    for(int i=0; i<nSklepow; i++)
    {
        for(int j=0; j<nProduktow; j++)
        {
            cin >> temp;
            ceny[i][j] = temp;
        }
    }

    int minimalnaCena = -1;
    for(int i=0; i<nSklepow; i++)
    {
        for(int j=i+1; j<nSklepow; j++)
        {
            int wynik = policz(ceny[i], ceny[j], nProduktow);
            if(minimalnaCena == -1)
            {
                minimalnaCena = wynik;
                continue;
            }
            if (minimalnaCena > wynik)
                minimalnaCena = wynik;
        }
    }

    cout << minimalnaCena << endl;

    return 0;
}
