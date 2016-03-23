#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;

int main() {
	
	int n;
	int wynik;
	string ost;
	cin >> n;
	wynik = 1;
	for (int i=1; i<=n; i++) {
		wynik = 2*wynik;
	}
	
	ostringstream ss;
	ss << wynik;
	string str = ss.str();
	/* cout << str << endl; */
	int dl = str.length();
	/* cout << dl << endl; */
	
	ost = str[str.size()-1];
	cout << ost;
}


