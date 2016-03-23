#include <iostream>
using namespace std;

int NWD(int a, int b) {
	int r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

int main() {
int n;
cin >> n;
int t[n];

for (int i = 0; i < n; i++)
    cin >> t[i];

int pom;
pom = NWD(t[0], t[1]);
for (int j = 2; j <= n-1; j++)
    pom = NWD(pom, t[j]);

cout << pom;
}
