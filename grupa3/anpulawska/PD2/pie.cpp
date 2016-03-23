#include <iostream>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];
        
    int pierwszy = -1;
    int ostatni = -1;
    for (int i = 0; i < n; i++){
        if (t[i]==x)
        ostatni = i + 1;
        }
    for (int i = n-1; i >= 0; i--)
        if (t[i] == x)
        pierwszy = i + 1;
cout << pierwszy << " " << ostatni << endl;       
}
