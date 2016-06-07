#include <iostream>
using namespace std;


int NWD(int a, int b) {

	int r = a % b;	
	while (r != 0) {
		a = b; b = r; r = a%b;
	}
	return b;
}


int main()
{
	int n;
	int n_w_d;

	cin >> n;
	int* t = new int [n];
	for (int i = 0; i < n; i++){
		cin >> t[i];
	}

	n_w_d = t[0];
	for (int i = 1; i < n-1; i++) {
		n_w_d = NWD(t[i], n_w_d);
	}

	cout << n_w_d << endl;
	
	system("pause");
	delete[] t; 
	cin.get();
	return 0;
}
