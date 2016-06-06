#include<iostream>
#include<vector>
using namespace std;

//program powinien umiec szybko wyszukiwac pierwsze wystapienie i ostatnie danej predkosci
//skoro tablica z predkosciami jest juz uporzadkowana w kolejnosci niemalejacej to wyszukiwanie
//dzielac cala tablice za kazdym razem na dwie czesci


int first_time(int szukana, int tab[], int n){

lewy=0;// przechowuje numer lewego krańca tablicy,
prawy=n-1; //− przechowuje numer prawego krańca tablicy,

while(lewy<=prawy)
  {
    srodek = (lewy + prawy)/2;//− przechowuje numer środkowego elementu tablicy.

    if(tab[srodek] == szukana)
      return srodek;

    if(tab[srodek] > szukana)
      prawy = srodek - 1;

    else
      lewy = srodek + 1;
}

  return -1; //zwracamy -1, gdy nie znajdziemy elementu
}

int last_time(int szukana, int tab[], int first, int n){
 //procedura jest taka sama, ale tutaj nie zaczynamy szukania od miejsca zerowego w tablicy,
 //tylko od miejsca = first_time
lewy=first;// przechowuje numer lewego krańca tablicy,
prawy=n-1; //− przechowuje numer prawego krańca tablicy,

while(lewy<=prawy)
  {
    srodek = (lewy + prawy)/2;//− przechowuje numer środkowego elementu tablicy.

    if(tab[srodek] == szukana)
      return srodek;

    if(tab[srodek] > szukana)
      prawy = srodek - 1;

    else
      lewy = srodek + 1;
}

  return -1; //zwracamy -1, gdy nie znajdziemy elementu

}


int main()
{
  int n;
   cin>>n; //podajemy ilość elementów do wczytania n < 1000000

    int tab[n];
  for(int i=0;i<n;i++)
    cin>>tab[i]; //wczytanie elementów tablicy

 //liczba pytan
 int q;
 cin >> q;

 //do tablicy o rozmiarze q wrzucane szukane predkosci
 int tab_szuk[q];
 for(int i=0;i<q;i++)
    cin>>tab_szuk[i]; //wczytanie elementów tablicy

//petla do szukania kolejnych predkosci z tablicy tab_szuk

//glowne wyszukiwanie
 for(int i=0;i<q;i++){

     int pozycja_1 = first_time(tab_szuk[i], tab, n);

     if(pozycja_1==-1)
            cout<< 0 <<endl;

     else{
    int pozycja_2 = last_time(tab_szuk[i], tab, pozycja_1, n);
    cout<<pozycja_2 - pozycja_1 +1 << end1;}
 }

}

