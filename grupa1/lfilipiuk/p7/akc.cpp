#include <iostream>

using namespace std;

int pierwszy(int tablica[], int n, int x){
int poczatek = 0;
int koniec = n - 1;
int srodek;
while (poczatek < koniec)
{
    srodek = (poczatek + koniec) / 2;
    if (tablica[srodek] >= x)             // na środku jest element większy lub równy x...
        koniec = srodek;                  // zatem x jest w przedziale [poczatek, srodek]
    else                                  // wiemy, że na środku jest element mniejszy od x...
        poczatek = srodek + 1;            // zatem x jest w przedziale [srodek+1, koniec]
}
if(tablica[poczatek]==x)
    return poczatek;
else
    return -1;
}

int ostatni(int tablica[], int n, int x){
int poczatek = 0;
int koniec = n - 1;
int srodek;

while (poczatek < koniec)
{
	srodek = (poczatek + koniec + 1) / 2;           // to jest dzielenie przez 2 z zaokrągleniem w górę
	if (tablica[srodek] <= x)
		poczatek = srodek;
	else
		koniec = srodek - 1;
}

if(tablica[poczatek]==x)
    return poczatek;
else
    return -1;
}

int main(){

int rozmiar;
cin >> rozmiar;
int * tablica = new int[rozmiar];

for(int i=0;i<rozmiar;i++)
    cin>>tablica[i];

int ile;
int liczba;
int a, b;
cin >> ile;
for(int i=0;i<ile;i++){
    cin >> liczba;
    a = pierwszy(tablica,rozmiar,liczba);
    b = ostatni(tablica,rozmiar,liczba);
    if(a<0 && b<0)
    cout << 0 << endl;
    else
    cout << b - a + 1 << endl;
}

}
