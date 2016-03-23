#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
int n;
int m;
int wyn;
int kon = 99999999;

cin >> n;
cin >> m;

int t[n][m];

for(int i=0;i<n;i++)
{
    for(int j=0;j<m;j++)
        {        cin >> t[i][j];
        }
}
for(int i=0;i<n-1;i++)
    {
    for(int j=i;j<n;j++)
        {
        for(int s=0;s<m;s++)
            {
            wyn=wyn+min(t[i][s],t[j][s]);
            }
        kon = min(kon, wyn);
        wyn=0;
        }
    }
cout<<kon;
}
