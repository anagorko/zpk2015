#include<iostream>
using namespace std;

int main() {
	// deklaracja zmiennych
	int n;

	// wczytywanie
	cin >> n;

	// deklaracja tablicy (dynamicznej) z liczbami
	int * tablica = new int[n];

	// wpisywanie liczb
	for (int i = 0; i < n; i++)
		cin >> tablica[i];

	// liczby zuzi (co druga od t[0] wlacznie)
	for (int i = 0; i < n; i += 2)
		cout << tablica[i] << " ";
	cout << endl;

	// liczby antka (co druga od t[1] wlacznie)
	for (int i = 1; i < n; i += 2)
		cout << tablica[i] << " ";
	cout << endl;
	
	// poprawka (2016-03-29): zbilansowanie uzycia new i delete
	delete[] tablica;
}
