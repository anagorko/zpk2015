#include<iostream>
using namespace std;

int max(int t[], int n) {
    int wyn = t[0];
    for(int i = 1; i < n; i++)
        if(t[i] > wyn)
            wyn = t[i];
    return wyn;
}

int wice(int t[], int m, int n) {
    int wice = 0;
    for(int i=0; i<n; i++)
        if(t[i]>wice && t[i]<m)
            wice = t[i];
    return wice;
}

int main(){
    int n;
    cin >> n;
    int t[n];

    for(int i=0; i<n; i++)
        cin >> t[i];

    int mistrz = max(t,n);
    int wicemistrz = wice(t,mistrz,n);

    cout << wicemistrz;
}
