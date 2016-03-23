#include <iostream>
using namespace std;
 
 bool czy_pierwsza(int n) {
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
    return true;
}
 
 
int main() {
    
    int k;
    cin >> k;
    if (czy_pierwsza(k)) 
        cout<<"pierwsza";
    else
        cout<<"zlozona";
    
}
