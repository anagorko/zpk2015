#include <iostream>
using namespace std;

/* program powinien obliczyc, ile liczb z przedzialu od a do b jest podzielnych przez k*/

int main() {
    int a, b, k, i, c;
    
	c==0;
    
    cin >> a >> b >> k;
    for (i=a; i<=b; i++){
    	
        if (i%k==0)
        c++;
    }
    cout << c-1 << endl; /* c-1 bo ostatnie c jest o 1 za wysokie*/
}
