#include <iostream>
using namespace std;

int main(){
	int n;
	cin >> n;
	
	if (n==0)
	    cout << 1;

	if (n%4==1)
		cout << 2;
	
	if (n%4==2)
		cout << 4;
	
	if (n%4==3)
		cout << 8;
	
	if (n%4==0 && n!=0)
		cout << 6;
}
	
