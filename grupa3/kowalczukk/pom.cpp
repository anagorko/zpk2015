#include <iostream>
using namespace std;

int main(){
    int suma=0;
    int n;
    int i=0;
    while (n>=0) {
        cin >> n;
        if (n>i && n>=0){
            suma++;
            i=n;
        }

    }
    cout << suma << endl;
}
