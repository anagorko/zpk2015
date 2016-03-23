#include <iostream>
using namespace std;

int main() {
    int n, x, i;
    int pierwszy =0;
    int ostatni = 0;
    cin >> n >> x;
    int a[n];
    for (i = 0; i < n; i++)
        cin>> a[i];
    for (i = 0; i < n; i++) {
        if (a[i] == x && pierwszy == 0)
            pierwszy = i+1;
        if (a[i] == x)
            ostatni = i+1;
}
        if(pierwszy ==0) { cout << "-1" << " " <<"-1";}
        else
   {

    cout << pierwszy << " " << ostatni; }
    return 0;
}
