#include <iostream>
using namespace std;

int pierwsza(int tab[], int startowa, int koncowa, int szukana){
    int srodkowa;
    while (koncowa > startowa){
        srodkowa = (koncowa + startowa) / 2;
        if (tab[srodkowa] >= szukana)
			koncowa = srodkowa;
		else
			startowa = srodkowa + 1;
    }

	return startowa;

}

int ostatnia(int tab[], int startowa, int koncowa, int szukana){
    int srodkowa;
    while (koncowa > startowa){
        srodkowa = (koncowa + startowa + 1) / 2;
        if (tab[srodkowa] <= szukana)
			startowa = srodkowa;
		else
			koncowa = srodkowa - 1;
    }

	return startowa;
}

int main() {

    int n;
    cin >> n;
    int tab[n];
    for(int i=0; i<n; i++) {
        cin>>tab[i];
    }

    int x;
    cin>>x;
    int tab2[x];
    for(int i=0; i<x; i++) {
        cin>>tab2[i];
    }

    int a[x];

    for(int i=0; i<x; i++) {
      int pierwszaa = pierwsza(tab, 0, n-1, tab2[i]);
      int ostatniaa = ostatnia(tab, 0, n-1, tab2[i]);

      a[x] = ostatniaa - pierwszaa + 1;
  }

    cout<<a[x]<<endl;

}
