#include <iostream>
using namespace std;

int druga_najwieksza(int t[], int n){
    int first = 0;
    int sec = 0;
    for (int i = 0; i < n; i++){
        if (t[i] > first){sec = first; first = t[i];}
        else if (t[i] > sec) {sec =t[i];}
    }
    return sec;
}

int main() {
    int n;
    cin >> n;
    int t[n];

    for (int i = 0; i < n; i++)
        cin >> t[i];
    cout << druga_najwieksza(t, n) << endl;
}

