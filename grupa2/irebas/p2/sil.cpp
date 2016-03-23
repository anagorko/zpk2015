#include <iostream>
using namespace std;

int main() {
	int a;
	int silnia;
	cin >> a;
	silnia = 1;
	for (int i = 1; i < a; i++) {
	silnia = silnia * (i + 1);
	
	}
	
	cout << silnia;
	
}
