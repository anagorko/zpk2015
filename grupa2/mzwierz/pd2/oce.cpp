#include <iostream>
using namespace std;

int main(){

    int n;
    cin >> n;
    int  t[n];
    int  liczba_ocen[6];

    for (int i = 0; i <= n - 1; i++)
        cin >> t[i];

    for (int i = 0; i <= 5; i++)
        liczba_ocen[i] = 0;

    for (int i = 0; i <= n - 1; i++)
        liczba_ocen[t[i] - 1]++;

    for (int i = 0; i <= 5; i++)
            cout << liczba_ocen[i] << " ";

}
