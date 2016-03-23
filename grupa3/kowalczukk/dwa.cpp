#include <iostream>
using namespace std;

int mniej(int a, int b) {
    if(a<=b)
        return a;
    else
        return b;
}


int main() {
    int market, produkt;
    cin >> market >> produkt;
    int t[market][produkt];
    for(int i=0; i<market; i++) {
        for(int j=0; j<produkt; j++) {
            cin >> t[i][j];
        }
    }
    int suma=0;
    int minimum=0;
    for(int i=0; i<produkt; i++) {
        minimum=minimum + mniej(t[0][i], t[1][i]);
    }
    for(int i=0; i<market-1; i++) {
        for(int z=1; z<market; z++) {
            for(int j=0; j<produkt; j++) {
                suma=suma+mniej(t[i][j],t[z][j]);
            }
        if (suma<minimum)
            minimum = suma;
        suma = 0;
        }
    }
    cout << minimum;
}
