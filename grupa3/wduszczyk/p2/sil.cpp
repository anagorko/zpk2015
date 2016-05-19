#include <iostream>
#include <string>

using namespace std;

int main()
{
int n, w;
cin>>n;

w=1;

for (int i = 1; i <=n; i++)
    w*=i;

cout<<w<<endl;
}
