#include <iostream>
using namespace std;

int min(int t[], int n) {
    int wyn = t[0];
    for (int i = 1; i < n; i++)
        if (t[i] < wyn)
            wyn = t[i];
    return wyn;
}

int main() {
    int n;
    int licznik;
    int nwd;
    int minimalna;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
        minimalna = min(t, n);
    
    /*    cout << min(t, n)  << endl; */
        
    /* teraz dzielniki */
    
    for (int i=minimalna; i >= 0; i--) {
    	licznik = 0;
    	if (minimalna % i == 0) {
    		for (int j=1; j<n; j++) {
    			if (t[j] % i == 0) {
    				licznik++;
    			}
    		}
    	}
    
    if (licznik == (n-1)) {
    	nwd = i;
    	break;
    }
    
    }
    cout << nwd << endl;
        
}
