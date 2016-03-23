#include <iostream>
using namespace std;

int main()
{
	
	int n, x;
	cin >> n >>x;
	
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];
	
	int d1=-1;
	int d2=d1;
	
	for (int j=0; j<n; j++) {
		if (t[j]==x){
			d1=j+1;
			break;
		}		
	}
	cout << d1 << " ";
	
		for (int j=n-1; j>=0; j--) {
		if (t[j]==x){
			d2=j+1;
			break;
		}		
	}
	cout << d2 << endl;
}