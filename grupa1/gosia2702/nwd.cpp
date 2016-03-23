#include<iostream>
#include<cstdlib>
using namespace std;

int NWD(int a, int b)
{
    while(a!=b)
       if(a>b)
           a-=b;
       else
           b-=a;
    return a;
}

int main()
{
    int i, n;
    cin>>n;

    int a[n-1];
    cin>>a[0];
    for(i=1;i<n;i++)
        {cin>>a[i]; a[i]=NWD(a[i],a[i-1]); }

    cout<<a[n-1];

}
