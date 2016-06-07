#include <iostream>
using namespace std;

int NWD(int a, int b){

int r=a%b;
while(  r!= 0){
    a=b;
    b=r;
    r=a%b;
}
return b;


}

int main(){

int k;

cin >> k;
int t[k];

for(int i=0; i<k; ++i)
    cin>>t[i];

int wyn= NWD(t[0],t[1]);

for(int i=2;i<k;++i) {
    wyn=NWD(wyn,t[i]);
}

cout<< wyn << endl;


}
