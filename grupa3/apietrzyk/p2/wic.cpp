#include <iostream>
using namespace std;

int main(){
	int n;
	cin >> n; 
	
	int t[n];
	for (int i = 0; i <n ; i++)
		cin >> t[i];
	
	int max=0;
	int j=0;
	
	for (int i=0; i<n; i++){
		if (t[i]>max){
			max=t[i];
			j=i;
		}
	}
	t[j]=0;
	
	max=0; 
	
	for (int i=0; i<n ; i++){
	    
		if (t[i]>max){
			max=t[i];
		}
	}
	
	cout << max;
}

