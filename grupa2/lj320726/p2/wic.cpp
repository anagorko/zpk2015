#include <iostream>
using namespace std;
 

int main() {

int n,m,w;
cin >> n;
int t[n];

for (int i=0;i<n;i++)
{   cin >> t[i];
}

w=0;
m=0;

for(int i=0; i<n;i++)
{  if(t[i]>m)
        m=t[i];
}

for(int i=0;i<n;i++)
{
    if(t[i]!=m && t[i]>w)
        w=t[i];
}

cout<<w;
}
