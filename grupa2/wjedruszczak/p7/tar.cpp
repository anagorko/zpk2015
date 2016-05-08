#include<iostream>
#include<string>
#include<vector>
using namespace std;

// prototyp funkcji, ktora szuka x dla zadanych p i q
string szukajBinarnieX(long long, long long);

int main() {
	int z;
	long long p, q;
	vector <string> wyniki;
	
	cin >> z;
	
	for (int i = 0; i < z; ++i) {
		cin >> p >> q;
		wyniki.push_back(szukajBinarnieX(p, q));
	}

	for (int i = 0; i < wyniki.size(); ++i)
		cout << wyniki.at(i) << endl;
}

string szukajBinarnieX(long long p, long long q) {
	long long poczatek = { 0 }, koniec = { 1000000 }, x;

	while (poczatek < koniec) {
		x = (poczatek + koniec) / 2;

		// funkcja pow(x, 3) daje zly wynik
		if (x * x * x + x * p == q)
			return to_string(x);
		if (x * x * x + x * p > q)
			koniec = x;
		else
			poczatek = x + 1;
	}
	return "NIE";
}
