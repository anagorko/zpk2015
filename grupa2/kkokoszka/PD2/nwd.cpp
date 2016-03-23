#include <iostream>
using namespace std;

int NWD(int x, int y) {
    int reszta = x % y;
    while (reszta != 0) {
        x = y;
        y = reszta;
        reszta = x % y;
    }
    return y;
}
int main() {
   int n,dzielnik;
   cin >>n;
   int t[n];
   for (int i=0;i<n;i++)
    { cin >>t[i];
    }
    dzielnik = t[0];

    for(int i=1; i<n;i++)
        {dzielnik = NWD(dzielnik,t[i]);
        }
    cout << dzielnik;
}
