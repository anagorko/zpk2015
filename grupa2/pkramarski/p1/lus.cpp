#include <iostream>
using namespace std;

int main(){
    int a, b, c, i;
    cin >> a;
    while(a%10==0){
        a/=10;
    }
    while(a!=0){
        b = a/10;
        c = b*10;
        i = a-c;
        cout << i;
        a = b;
    }
}
