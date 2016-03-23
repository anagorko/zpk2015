#include <iostream>
#include <cmath>
using namespace std;
	
int main () {
    int n; 
	cin >> n; 
    int l = floor( log10(n)+1);
    int k = 0;
    for( int i=0; i<l; i++)
    {
             k+=pow(10.0, l - 1 - i )*(n%10);
             n=n/10;
    }
    cout << k;
}