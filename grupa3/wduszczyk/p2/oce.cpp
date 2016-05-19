// Example program
#include <iostream>
#include <string>
#include <math.h>  

using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];

    int licznik[6];
    for (int i = 0; i < 6; i++)
        licznik[i] = 0;

    for (int i = 0; i < n; i++){
        int ocena = t[i];
        licznik[ocena - 1] += 1;
    }


   for (int j =0; j < 6; j++)
        cout << licznik[j] << " ";
}
