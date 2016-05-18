#include <iostream>
#include <math.h>
using namespace std;

long long czyjest (long long p, long long q ) {
long long poczatek = 0;
long long koniec = pow(q,1/3.0);
long long srodek;

while (poczatek < koniec)
{
    srodek = (poczatek + koniec) / 2;
    if (srodek*srodek*srodek +srodek*p >= q )             // na środku jest element większy lub równy x...
        koniec = srodek;                  // zatem x jest w przedziale [poczatek, srodek]
    else                                  // wiemy, że na środku jest element mniejszy od x...
        poczatek = srodek + 1;            // zatem x jest w przedziale [srodek+1, koniec]
}

if (poczatek * poczatek * poczatek + p * poczatek == q)
    return poczatek;
else
    return -1;

}

int main()
{
    int z;
    cin >> z;

    long long p[z],q[z];

    for(int i=0;i<z;i++) {
        cin >> p[i]>>q[i];
    }

    for(int i=0;i<z;i++){

        if (czyjest(p[i],q[i]) >=0 ) {
            cout << czyjest(p[i],q[i])<<endl;
        }
        else {
            cout<<"NIE"<<endl;
        }
    }
}
