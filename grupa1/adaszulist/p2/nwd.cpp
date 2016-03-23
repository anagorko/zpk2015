#include <iostream>
using namespace std;
int NWD(int a, int b) {
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
int main(){
int n;
int wynik;
cin >> n;
int liczby[n];
for(int i = 0; i < n; i++)
    cin >> liczby[i];
wynik = NWD(liczby[0],liczby[1]);
for(int i = 2; i < n; i++)
    wynik = NWD(wynik,liczby[i]);
cout << wynik;
return 0;
}
