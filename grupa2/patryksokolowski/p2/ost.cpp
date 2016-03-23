#include <iostream>
using namespace std;

int main(){
    int n, x;
    cin >> n;
    if (n == 0){
        x = 1;
        cout << x << endl;
        return 0;
        }
    if (n % 4 == 1)
        x = 2;
    if (n % 4 == 2)
        x = 4;
    if (n % 4 == 3)
        x = 8;
    if (n % 4 == 0)
        x = 6;
    cout << x << endl;
}
