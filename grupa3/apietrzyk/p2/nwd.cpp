#include <iostream>
using namespace std;
 
int NWD (int a, int b){
int c;
	while (b!=0) {            
		c=a%b;
		a=b;
		b=c;        
	}
	return a;        
}
 
int main(){

int n;
cin >> n;

int t[n];
for (int i = 0; i < n; i++)
    cin >> t[i];
    
int nwd;
  
nwd = NWD(t[0],t[1]);

for(int i=2; i<n; i++)
	nwd = NWD(nwd,t[i]);
   
cout << nwd <<endl;

}