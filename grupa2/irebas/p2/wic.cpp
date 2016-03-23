#include <iostream>
using namespace std;

int max(int t[], int n) {
    int wyn = t[0];
    for (int i = 1; i < n; i++)
        if (t[i] > wyn)
            wyn = t[i];
    return wyn;
}

int max2(int t[], int n) {
    int wyn = t[1];
    for (int i = 1; i < n; i++)
        if (t[i] > wyn)
            wyn = t[i];
    return wyn;
}

int main() {
    int n;
    int licznik;
    int j;
    int maksymalna;
    cin >> n;
    int t[n];
    int t2[n-1];
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    maksymalna = max(t, n);
	/* cout << maksymalna << endl; */
	j = 0;   
    for (int i = 0; i < n; i++) {
    	if (t[i] != maksymalna) {
    		j++;
    		t2[j] = t[i];
    		/* cout << t2[j] << endl; */
    	}
    }
    
    cout << max2(t2, n-1) << endl;
        
}
