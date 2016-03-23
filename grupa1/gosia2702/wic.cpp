#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
    int i,n, ma, ma2;
    cin>>n;
    ma=0;
    ma2=0;
    int a[n-1];
    for(i=0;i<n;i++)
        {cin>>a[i]; if (a[i]>ma) {ma2=ma; ma=a[i]; } else{ if (ma2<a[i]) ma2=a[i];} }

    cout<<ma2;

}
