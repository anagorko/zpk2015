#include <iostream>
using namespace std;

long long szukaj(long long p, long long q) {

	long long start = 0;
	long long koniec = 1000000;
	long long x;

	while (start < koniec) {

		x = (start + koniec) / 2;
		if ((x * x * x + x * p) == q)
			return x;
		else if ((x * x * x + x * p) > q)
			koniec = x;
		else
			start = x + 1;

	}

	return 0; // liczba przypisana potem do rozw
}

int main() {

	int a;
	cin >> a;

	long long p[a], q[a];
	for (int i = 0; i < a; i++)
		cin >> p[i] >> q[i];

	long long rozw;

	for (int i = 0; i < a; i++) {

		rozw = szukaj(p[i], q[i]);

		if (rozw == 0) {
			cout << "NIE" << endl;
		}

		else {
			cout << rozw << endl;
        }
    }
}
