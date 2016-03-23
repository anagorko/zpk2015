#include <iostream>
using namespace std;

int main() {
	
	int a;
	cin >> a;
	
	bool pierwsza = true;
	
	int n=2;
		
	while (a>=n*n){
		if (a%n!=0)
			n++;
		if (a%n==0) {
			pierwsza = false;
			break;
		}
			
	}
	
	if (pierwsza==true)
		cout << "pierwsza" << endl;
	else 
		cout << "zlozona" << endl;	
}

