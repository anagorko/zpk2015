#include <iostream>
using namespace std;

int szukaj_pierwsza(int tab[], int pocz, int kon, int e){
    while (kon > pocz){

        int sr = (kon + pocz) / 2;

        if (tab[sr] >= e)
			kon = sr;
		else
			pocz = sr + 1;
    }

	if (tab[pocz] == e)
		return pocz;
	else
		return 0;
}

int szukaj_ostatnia(int tab[], int pocz, int kon, int e){
    while (kon > pocz){

        int sr = (kon + pocz + 1) / 2;

        if (tab[sr] <= e)
            pocz = sr;
         else
            kon = sr - 1;

    }

    if (tab[pocz] == e)
        return pocz;
     else
        return -1;

}

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++){
        cin >> t[i];
    }

    int q;
    cin >> q;
    int s[q];
    for (int i = 0; i < q; i++){
        cin >> s[i];
        
    int a = 0;
    bool is = false;

        int pierwsza = szukaj_pierwsza(t, 0, n - 1, s[i]);
        is = false;
        int ost = szukaj_ostatnia(t, a, n - 1, s[i]);
        if (pierwsza == -1 || ost == -1){
            cout << 0 << endl;
        } else{
            cout << ost - pierwsza + 1 << endl;
        }
    }
}
