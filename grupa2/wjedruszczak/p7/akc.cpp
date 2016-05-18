#include<iostream>
#include<vector>
using namespace std;

// prototyp funkcji, ktora zwraca indeks pierwszego wystapienia
// czastki lub 0 jezeli nie ma jej wsrod pomiarow
int szukajBinarniePierwsza(vector <int> &, int);

// prototyp funkcji, ktora zwraca indeks ostatniego wystapienia
// czastki (skorygowanego o + 1) lub 0 jezeli nie ma jej wsrod pomiarow
int szukajBinarnieOstatnia(vector <int> &, int);

int main() {
	int n, q, zapytanie;

	cin >> n;
	vector <int> czastki(n, 0), wyniki;

	for (int i = 0; i < n; ++i)
		cin >> czastki.at(i);

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> zapytanie;
		wyniki.push_back(szukajBinarnieOstatnia(czastki, zapytanie) - szukajBinarniePierwsza(czastki, zapytanie));
	}

	for (int i = 0; i < wyniki.size(); ++i)
		cout << wyniki.at(i) << endl;
}

int szukajBinarniePierwsza(vector <int> & v, int liczba) {
	int poczatek = { 0 }, koniec = { int(v.size() - 1) }, srodek;

	while (poczatek < koniec) {
		srodek = (poczatek + koniec) / 2;

		if (v.at(srodek) >= liczba)
			koniec = srodek;
		else
			poczatek = srodek + 1;
	}

	if (v.at(poczatek) == liczba)
		return poczatek;
	else
		return 0;
}

int szukajBinarnieOstatnia(vector <int> & v, int liczba) {
	int poczatek = { 0 }, koniec = { int(v.size() - 1) }, srodek;

	while (poczatek < koniec) {
		srodek = (poczatek + koniec + 1) / 2;

		if (v.at(srodek) <= liczba)
			poczatek = srodek;
		else
			koniec = srodek - 1;
	}

	if (v.at(poczatek) == liczba)
		return poczatek + 1;
	else
		return 0;
}
