#include <iostream>
using namespace std;

int main() {
    int n, ocena;
    cin >> n;
    int t[7];

    for (int i = 0; i <= 6; i++)
        t[i] = 0;

    for (int i = 1; i <= n; i++){
        cin >> ocena;
        t[ocena] +=1;
    }
    for (int i = 1; i <= 6; i++)
    cout << t[i] << " ";
}
