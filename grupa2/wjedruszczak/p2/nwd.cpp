#include<iostream>
using namespace std;

// funkcja nwd (wg materialow z kursu)
int nwd(int a, int b) {
	int r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

int main() {
	// deklaracja zmiennych
	int n, i;
	
	// wczytywanie
	cin >> n;
	
	// deklaracja tablicy (dynamicznej) z liczbami
	int * tablica = new int[n];
	
	// wczytywanie liczb
	for (i = 0; i < n; i++)
		cin >> tablica[i];

	// obliczenia
	int wynik = tablica[0];

	// obliczenia, c.d.
	for (i = 1; i < n; i++)
		wynik = nwd(wynik, tablica[i]);

	// wynik
	cout << wynik << endl;
	
	// poprawka (2016-03-29): zbilansowanie uzycia new i delete
	delete[] tablica;
}
