#include<iostream>
using namespace std;

int main() {
	unsigned long long i;
	cin >> i;
	while (i != 1 && i % 2 == 0)
        i = i / 2;
    if (i == 1)
        cout << "TAK" << endl;
    else{
        i = 3 * i + 3;
        cout << "NIE" << endl;
    }
}
