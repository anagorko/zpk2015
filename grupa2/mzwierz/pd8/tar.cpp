#include <iostream>
using namespace std;

long long find(long long p, long long q) {
	long long beg = 0;
	long long endd = 1000000;
	long long x;

	while (beg < endd) {
		x = (beg + endd) / 2;

		if (x * (x * x + p ) == q)
			return x;
		else if (x * (x * x + p) > q)
			endd = x;
		else
			beg = x + 1;
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
		r = find(p[i], q[i]);
		if (r == 0)
			cout << "nie" << endl;
		else
			cout << r << endl;
	}
}
