#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	// deklaracja zmiennych
	int n, i, rozneZero = 0, rozneN = 0;

	// wczytywanie
	cin >> n;

	// deklaracja tablicy (dynamicznej) z liczbami
	int * ciagLiczb = new int[n];

	// wczytywanie liczb
	for (i = 0; i < n; ++i)
		cin >> ciagLiczb[i];

	// obliczenia od poczatku
	for (i = 0; i < n; ++i) {
		if (ciagLiczb[i] != ciagLiczb[n - 1]) {
			rozneZero = n - 1 - i;
			break; // szukam najwiekszej odleglosci
		}
	}

	// obliczenia od konca
	for (i = n - 1; i > 0; --i) {
		if (ciagLiczb[i] != ciagLiczb[0]) {
			rozneN = i;
			break; // szukam najwiekszej odleglosci
		}
	}

	// wynik
	if (rozneZero == 0 && rozneN == 0)
		cout << "BRAK" << endl;
	else
		cout << max(rozneZero, rozneN) << endl;
		
	// poprawka (2016-03-29): zbilansowanie uzycia new i delete
	delete[] ciagLiczb;
}
