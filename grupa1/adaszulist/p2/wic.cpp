#include <iostream>
using namespace std;

int p[2] = {0,0};
void zwyciezcy(int a){
    if (a > p[0]){
        p[1]=p[0];
        p[0]=a;
    }
    else if(a > p[1] && a != p[0])
        p[1] = a;
}
void sortuj(int a, int b){
    if(a>b){
        p[0]=a;
        p[1]=b;
    }
    else{
        p[0]=b;
        p[1]=a;
    }
}

int main(){
int n;
cin >> n;
int punkty[n];
for(int i = 0; i < n; i++)
    cin >> punkty[i];
sortuj(punkty[0],punkty[1]);
for(int i = 2; i < n; i++){
    zwyciezcy(punkty[i]);
}
cout << p[1];
return 0;
}
