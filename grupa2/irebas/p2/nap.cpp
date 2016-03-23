#include <iostream>
using namespace std;

int main() {
	int a;
	cin >> a;
	int b[a];

	for (int i = 0; i < a; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < a; i+=2) {
		cout << b[i] << " ";
	}
	cout << endl;
	for (int i = 1; i < a; i+=2) {
		cout << b[i] << " ";
	}

}
