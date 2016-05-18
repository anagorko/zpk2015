#include <iostream>
using namespace std;

int n, r = 0;
bool jest = false;

int wyszukaj_pierwsza(int tabl[], int p, int k, int l){
    while (k > p){
        int sr = (k + p) / 2;
        if (tabl[sr] == l){
            if (r == 0){
                r = sr;
            }
        }
        if (tabl[sr] < l){
            p = sr + 1;
        } else{
            k = sr;
        }
    }
    if (tabl[k] == l){
       return k;
    } else{
        return -1;
    }
}


int wyszukaj_ostatnia(int tabl[], int p, int k, int l){
    while (k > p){
        int sr = (k + p + 1) / 2;
        if (tabl[sr] <= l){
            p = sr;
        } else{
            k = sr - 1;
        }
    }
    if (tabl[p] == l){
        return p;
    } else{
        return -1;
    }
}

int main() {
    int q;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++){
        cin >> t[i];
    }
    cin >> q;
    int s[q];
    for (int i = 0; i < q; i++){
        r = 0;
        cin >> s[i];
        jest = false;
        int pierw = wyszukaj_pierwsza(t, 0, n - 1, s[i]);
        jest = false;
        int ost = wyszukaj_ostatnia(t, r, n - 1, s[i]);
        if (pierw == -1 || ost == -1){
            cout << 0 << endl;
        } else{
            cout << ost - pierw + 1 << endl;
        }
    }
}
