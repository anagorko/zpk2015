#include <iostream>
using namespace std;

int main(){

int k;
cin >> k;
int waga[k], p[k];
int suma=0;
waga[0]=1;
waga[1]=2;
int x=0;


for(int i=2; i<=k;i++)
    waga[i]=waga[i-1]*2;

for(int i= 0; i<=k; i++){
    cin >> p[i];
}
suma=p[o]*waga[0];
x = suma +1

    for(int i =1 ;i<k; i++){
        if(x < waga[i])
        x+=p[i] *waga[i];
    }

cout<< x << endl;

}

















