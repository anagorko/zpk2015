#include <iostream>
#include <string>

using namespace std;

int main() {
  int i,a,b,k,w;
  cin >>a>>b>>k;
  w=0;
for(i = a; i <= b; i++){
    if (i%k==0){
    w++;}
  else {
  w+=0;}
    }    
cout<<w<<endl;
    }