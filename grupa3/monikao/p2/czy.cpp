#include <iostream>
using namespace std;

int main() {
    long long i;
    int k = 0;
    cin >> i;
    while (i != 1){
        if (i % 2 == 0){
            i = i / 2;
            k = 2;}
        else{
            k = 1;
            i = 1;
        }
    }
    /*zatrzyma si� jedynie dla pot�g liczby 2*/
    /*kolejne pot�gi liczby 2 maj� reszty 1 lub 2 z dzielenia przez 3
    je�eli raz wykonamy liczb� dzia��nie 3 * i + 3 = 3*(i+1) to otrzymamy liczb� podzieln� przez 3
    i ju� nigdy nie otrzyammy liczby 2**k*/
    if(k==2)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
