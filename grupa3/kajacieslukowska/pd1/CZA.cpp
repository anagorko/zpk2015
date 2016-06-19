#include <iostream>
using namespace std;

int main(){
    int a;
    cin >> a;

    int g = a/3600;
    int m = (a-3600*g)/60;
    int s = a-3600*g-60*m;
    cout << g << "g" << m << "m" << s << "s";
}
