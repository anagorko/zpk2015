#include<iostream>
using namespace std;

int main(){
    int a, b, c;
    cin >> a >> b >> c;
    if (a>0 && b>0 && c>0 && a>c && b>c && a%c!=0 && b%c!=0)
        cout << (a/c)*(b/c)-((a/c-2)*(b/c-2)) << endl;
    else if (a>0 && b>0 && c>0 && a>c && b>c && a%c==0 && b%c==0)
        cout << (a/c)*(b/c) << endl;
    else
        cout << 0 << endl;
}
