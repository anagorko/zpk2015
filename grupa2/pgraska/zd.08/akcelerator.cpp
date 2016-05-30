#include <iostream>

using namespace std;

int indexPoczatek(int* t, int size,int element);
int indexKoniec(int* t, int size,int _lewy, int element);

int main()
{
	int n;
	cin >> n;

	int* testy = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> testy[i];
	}

	int q;
	cin >> q;

	int* zapytania = new int[q];
	for (int i = 0; i < q; i++) {
		cin >> zapytania[i];
	}

	for (int i = 0; i < q; i++) {
		int indexLewy = indexPoczatek(testy,n,zapytania[i]);
		if (indexLewy != -1) {
			int indexPrawy = indexKoniec(testy,n,indexLewy,zapytania[i]);
			cout << (indexPrawy - indexLewy + 1) << "\n";
		}
		else {
			cout << "0" << "\n";
		}
	}

	system("pause");
	delete[] testy;
	delete[] zapytania;
	return 0;
}

int indexPoczatek(int* t, int size, int element) {
	int lewy = 0;
	int prawy = size - 1;
	int srodek = (lewy + prawy) / 2;

	while (lewy < prawy) {
		if (t[srodek] < element) {
			lewy = srodek + 1;
		}
		else {
			prawy = srodek;
		}
		srodek = (lewy + prawy) / 2;
	}

	if (t[lewy] == element) {
		return lewy;
	}
	else {
		return -1;
	}
}
int indexKoniec(int* t, int size,int _lewy, int element) {
	int lewy = _lewy;
	int prawy = size - 1;
	int srodek = (lewy + prawy + 1) / 2;
	while (lewy < prawy) {
		if (t[srodek] > element) {
			prawy = srodek - 1;
		}else {
			lewy = srodek;
		}
		srodek = (lewy + prawy + 1) / 2;
	}

	if (t[prawy] == element) {
		return prawy;
	}else{
		return -1;
	}
}
