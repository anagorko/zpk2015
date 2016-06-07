#include <iostream>
using namespace std;

int main(){
    int a=0;
    int pom=0;
    int i=0;

    while (a!=-1 && a<1000000){
        cin >> a;
        if (a>pom){
            pom = a;
            i++;
        }
    }
    cout << i << endl;
}
