#include <iostream>
using namespace std;


int sort(int* p, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int max = p[0];
		int pom = 0;
		for (int j = 1; j <= i; j++) {
			if (p[j] > max) {
				
				pom = j;
				max = p[pom];
			}
		}
		p[pom] = p[i];
		p[i] = max;
	}
	return p[n-2];
}



int main() {
	int n;
	cin >> n;
	int* p = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	cout << sort(p, n) << endl;

	system("pause");
	cin.get();
	return 0;
}
