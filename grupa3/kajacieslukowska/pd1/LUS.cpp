#include <iostream>
using namespace std;

int main(){
    int n;
    int i = 0;
    cin >> n;
    while( n > 0) {
        i = i*10 + n%10;
        n = n/10;
    }
    cout << i;
}
