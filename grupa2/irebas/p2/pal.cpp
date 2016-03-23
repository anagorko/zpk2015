#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main() {
	string napis2;
	string napis;
	cin >> napis;
	string wyraz;
	int i;
	int a = napis.length();
	
		for (i=0; i<a; i++) {
			napis2[i] = napis[a - i - 1];
			wyraz = wyraz + napis2[i];
			/* cout << napis2[i]; */
		}
	
	/* cout << wyraz << endl; */
	
	if (napis == wyraz) {
		cout << "TAK";
	}
	else {
		cout << "NIE";
	}
	
}
