#include <iostream>
using namespace std;

long long znajdz(long long p, long long q) {
	long long pocz = 0;
	long long kon = 1000000;
	long long x;

	while (pocz < kon) {
		x = (pocz + kon) / 2;

		if (x * (x * x + p ) == q)
			return x;
		else if (x * (x * x + p) > q)
			kon = x;
		else
			pocz = x + 1;
	}
	return 0;
}

int main() {

	int a;
	cin >> a;
	long long p[a], q[a];
	for (int i = 0; i < a; i++)
		cin >> p[i] >> q[i];

	long long r;
	for (int i = 0; i < a; i++) {
		r = znajdz(p[i], q[i]);
		if (r == 0)
			cout << "nie" << endl;
		else
			cout << r << endl;
	}
}
