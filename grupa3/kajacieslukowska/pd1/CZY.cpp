#include <iostream>
using namespace std;

int main(){
    long long int n;
    cin >> n;
    bool czy = true;

    while( czy == true && n != 1) {
        if( n%2 != 0)
            czy = false;
        else
            n = n/2;
    }

    if( czy == true)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
