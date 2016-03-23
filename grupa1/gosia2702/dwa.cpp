#include <iostream>
using namespace std;

int main() {
    int i,j,n, m,k, mi,su, su1;
    su=0;
    su1=0;
    cin >> n >> m;
    int a[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
 su1=0;
 for(i=0;i<m;i++) su1=su1+a[1][i];

   for(i=0;i<n;i++){
    for(j=i+1;j<n;j++)
     {   for(k=0;k<m;k++)  {
         if(a[i][k]<a[j][k]){ su=su+a[i][k];}
            else { su=su+a[j][k];}
        }
        if (su<su1) {su1=su;} su=0;
     }

      }
 cout<<su1;
}
