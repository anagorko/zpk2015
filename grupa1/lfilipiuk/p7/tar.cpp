#include <iostream>
#include <cmath>

using namespace std;

long long wielomian(long long p, long long q, int x){
    return pow(x,3)+x*p-q;
}

int main(){

// x^3 + p*x - q = 0
long long p,q;
int poczatek,koniec,srodek;


int ile;
cin >> ile;

for (int i=0;i<ile;i++){
poczatek = 0;
koniec = 1000000;
cin >> p >> q;

while(poczatek < koniec){
    srodek = (poczatek + koniec) / 2;
    if (wielomian(p,q,srodek) >= 0)       // na środku jest element większy lub równy 0...
        koniec = srodek;                  // zatem 0 jest w przedziale [poczatek, srodek]
    else                                  // wiemy, że na środku jest element mniejszy od 0...
        poczatek = srodek+1;              // zatem 0 jest w przedziale [srodek+1, koniec]

}

    if(wielomian(p,q,poczatek)==0)
        cout<<poczatek<<endl;
    else
        cout<<"NIE"<<endl;

}
}
