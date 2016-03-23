#include <iostream>
using namespace std;

int main(){
    long long int i;
    cin >> i;
    /*while (i != 1) {
        if (i % 2 == 0)
            i = i / 2;
        else
            i = 3 * i + 3;
    cout << i << endl;
    }*/
    while (i > 2 && i%2==0) {
        i/=2;
    }
    if (i==2)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
