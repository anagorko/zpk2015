#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int countOstatniaSzukanaWielkosc;	// ograniczenie ilości wyników do przeszukania
int countOstatniaSzukanaPozycja;	// zapisanie ostatniej pozycji ostatniego

int count(int * predkosci, int iloscPomiarow, int szukanaWielkosc){
	if(predkosci[0] > szukanaWielkosc || predkosci[iloscPomiarow-1] < szukanaWielkosc) return 0;	// aby nie szukac poza zakresem
	if(countOstatniaSzukanaWielkosc > szukanaWielkosc){
		countOstatniaSzukanaPozycja = (countOstatniaSzukanaPozycja+iloscPomiarow)/2; // polowa zbioru
	}
	else if(countOstatniaSzukanaWielkosc < szukanaWielkosc){
		countOstatniaSzukanaPozycja = countOstatniaSzukanaPozycja+iloscPomiarow/2; // polowa zbioru ograniczonego
	}
	else{
		// na poczatek
		while(countOstatniaSzukanaPozycja > 0 && predkosci[countOstatniaSzukanaPozycja-1] == szukanaWielkosc) countOstatniaSzukanaPozycja--;
		// zliczenie
		int ilosc = 1;	// pomijamy to na czym jestesmy i wiemy, ze jest naszym wynikiem
		while(countOstatniaSzukanaPozycja < iloscPomiarow && predkosci[countOstatniaSzukanaPozycja+1] == szukanaWielkosc){
			countOstatniaSzukanaPozycja++;
			ilosc++;
		}
		//zwrocenie wyniku
		return ilosc;
	}
	countOstatniaSzukanaWielkosc = predkosci[countOstatniaSzukanaPozycja]; // rekursja
	return count(predkosci, iloscPomiarow, szukanaWielkosc); // przekazanie wyniku dalej
}

int main(int argc, char** argv) {
	int n;	// pierwszy parametr
	do {
		scanf("%d", &n);
	}while(n<0 || n > 100000);
	char predkosci[11*n];	// zmienna na 100 000 liczb + 100 000 spacji
	fflush(stdin);	// czyszczenie bufora (???)
	fgets(predkosci, 11*n, stdin);	// pobieramy do 11*n zankow, kończąc enterem
	int iPredkosci[n];
	int i;
	iPredkosci[0] = atoi(strtok(predkosci, " "));
	for(i = 1; i < n; i++) iPredkosci[i] = atoi(strtok(NULL, " "));
	int q;
	do {
		scanf("%d", &q);
	}while(q<0 || q > 1000000);
	int zapytania[q];
	for(i = 0; i < q; i++) scanf("%d", zapytania + i);
	countOstatniaSzukanaPozycja = 0;
	countOstatniaSzukanaWielkosc = iPredkosci[0];
	for(i = 0; i < q; i++) printf("dla predkosci %d: %d wynikow\n", zapytania[i], count(iPredkosci, n, zapytania[i]));

    return 0;
}
