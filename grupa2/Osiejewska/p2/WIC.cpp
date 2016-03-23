#include<iostream>
#include<cstdlib>
using namespace std;

int sort(int t[],int n){
int pom;
  for(int i=0;i<n;i++)
    for(int j=0;j<n-i-1;j++)
        if(t[j]<t[j+1]){
            pom = t[j];
            t[j] = t[j+1];
            t[j+1] = pom;
        }
    return t[1];
}

int main(){
int n;
cin>>n;
int t[n];
  for(int i=0; i<n; i++)
    cin>>t[i];

  cout << sort(t,n) << endl;
}
