#include <iostream>
#include <algorithm>
using namespace std;
 
int main() 
{
    int n, m, suma, suma2;
   
    cin >> n >> m;
    int mark[n][m];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            cin >> mark[i][j];
        }
    }
	
	suma=99999;
	
    for (int i=0; i<n-1; i++) {
    	for (int k=1; i+k<n; k++) {
    		suma2=0;
        	for (int j=0; j<m; j++) {
        		suma2=suma2 + min(mark[i][j], mark[i+k][j]);
        	}
            	suma = min(suma, suma2);
    	}
    }
    cout << suma;
     
}
