#include <iostream>

using namespace std;


int NWD(int a, int b) {
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int main()
{
    int n, k, NWD_stare, NWD_nowe;
    cin >> n;
    
    int tab[n];
    cin >> tab[0] >> tab[1];
    
        NWD_stare = NWD(tab[0], tab[1]);
        
        if (n == 2)
        
            cout << NWD_stare;
        
        else {
            for (int i=2; i < n; i++) { //wczytywanie i wypisywanie
                cin >> k;
                NWD_nowe = NWD(NWD_stare, k);
                NWD_stare = NWD_nowe;
            }

            cout << NWD_nowe;
        }
return 0;
}
