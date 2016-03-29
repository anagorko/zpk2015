#include<iostream>
using namespace std;

int main(){
    int a, b, k;
    cin >> a >> b >> k;
    if(a%k==0)
        cout << ((b/k) - (a/k)) + 1 << endl;
    else
        cout << ((b/k) - (a/k)) << endl;
}
