#include <iostream>
#include <algorithm>
using namespace std;
 
int main() 
{
int i;
cin >> i;
do {
	if (i%2 == 0) {
		i = i / 2;
	}
	else {
		i = 3*i + 3;
	}
	cout << i << endl;
	
	if (i == 1) {
	cout << "TAK";
	break;
	}
	
	if (i == 3) {
	cout << "NIE";
	break;
	}
	
} while (i != 1);


}
