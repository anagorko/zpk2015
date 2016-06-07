#include <iostream>
using namespace std;

int main(){

int m;
int b=0;
int k=10;

cin>>m;

while(m%10==0){
    m=m/10;
}


while(m!=0){
    b=m%k;
    cout << b;
    m=m/k;
}
}
