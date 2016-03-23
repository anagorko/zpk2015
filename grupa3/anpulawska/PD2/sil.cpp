#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int silnia = 1;
    if (n == 0)
        cout << silnia <<endl;
    else {
        for (int i = 1; i <= n; i++){
             silnia *=  i;
        }
        cout << silnia <<endl;
        }
}
