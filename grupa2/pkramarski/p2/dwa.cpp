#include <iostream>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    int t[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cin >> t[i][j];
    }

    int zakupy = 1000000;
    int rachunek;

    for(int i=0; i<n-1; i++) {
    	for(int k=1; i+k<n; k++) {
    		rachunek = 0;
        	for(int j=0; j<m; j++) {
        		rachunek = rachunek + min(t[i][j], t[i+k][j]);
        	}
            	zakupy = min(zakupy, rachunek);
    	}
    }
    cout << zakupy << endl;
}
