#include<iostream>
using namespace std;

// funkcja wyznaczWicemistrza
int wyznaczWicemistrza(int tablica[], int n) {
	// deklaracja zmiennych
	int i, mistrz = tablica[0], wicemistrz = 0, indeksWicemistrz = 0;

	// szukam mistrza
	for (i = 1; i < n; i++)
		if (tablica[i] > mistrz)
			mistrz = tablica[i];

	// szukam wicemistrza
	for (i = 0; i < n; i++)
		if (tablica[i] < mistrz && tablica[i] > wicemistrz) {
			wicemistrz = tablica[i];
			indeksWicemistrz = i;
		}

	// indeks tablicy z wynikiem wicemistrza
	return indeksWicemistrz;
}

int main() {
	// deklaracja zmiennych
	int n, i;

	// wczytywanie
	cin >> n;

	// deklaracja tablicy (dynamicznej) z liczbami
	int * wyniki = new int[n];

	// wczytywanie liczby punktow
	for (i = 0; i < n; i++)
		cin >> wyniki[i];
	
	// wynik
	cout << wyniki[wyznaczWicemistrza(wyniki, n)] << endl;
	
	// poprawka (2016-03-29): zbilansowanie uzycia new i delete
	delete[] wyniki;
}
