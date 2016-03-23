#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;
    int a[n], b[7];
    for(int i=0;i<6;i++)
        {b[i]=0;}


    for(int i=0;i<n;i++)
        {cin>>a[i]; b[a[i]-1]=b[a[i]-1]+1; }

   for(int i=0;i<6;i++)
        {cout<<b[i]<< " ";}
}
