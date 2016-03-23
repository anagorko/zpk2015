#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int i=1, pot10=1, lustro=0;
    while (n>0) {
        i=n%(10);
        n/=10;
        lustro=lustro*10+i;
    }
    int r = lustro%10;
    while (r==0) {
        lustro=lustro/10;
        r = lustro%10;
    }

    cout << lustro;
}
